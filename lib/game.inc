<?php
/***************************************************
 * Hello world Top Page
 *
 * @package
 * @access  public
 * @author
 * @create
 * @version
 ***************************************************/

require_once('base_model.inc');

//ブラックジャック関するクラス
class Blackjack extends base_model{

	//ブラックジャック開始時の処理
	public function execute() {
	
		include("header.inc");
	
		//ゲームをリロードしようとしたらエラー
		if(@$_SESSION['parent'] != null){
			//セッションを消して
			unset($_SESSION['parent']);
			//エラーページに飛ぶ
			header("Location: http://localhost/PHPBJ/wwwroot/error.html");
		}

		//ゲーム名をセッションに登録
		$_SESSION["game_name"] = "BlackJack";
		//smartyを使うためのインスタンスを作る
		$smarty = $this->get_conv();
		//親のインスタンスを作る
		$parent = new Player();
		//プレイヤーのインスタンスを持ってくる
		$player = unserialize($_SESSION['player']);
		//参加者たちの配列
		//$players_arr = array($parent,$player);
		
		//継続してゲームの場合、プレイヤーのカードを初期化
		if($player->get_player_card() != null){
			$player->set_player_card(array());
		}
			
		//ゲームを始めるにあたってトランプを作る
		$card = new Card();
		$now_use_tramp = $card->get_All_tramp();
		
		//トランプを混ぜる
		shuffle($now_use_tramp);
		
		//カードを親とプレイヤーに配る
		$now_use_tramp = $card->deal_tramp($now_use_tramp,2,$parent,$player);
				
		//セッションに情報を格納
		$_SESSION['now_use_tramp'] = $now_use_tramp;
		$_SESSION['parent'] = serialize($parent);
		$_SESSION['player'] = serialize($player);
		
		//表示側に渡す
		//表示側に毎回渡すものを渡す
		$utility->common_display($player,$parent,$smarty);
				
	}
}


class Poker extends base_model{

	public function execute() {
		$conv = $this->get_conv();
		//ゲーム名をセッションに登録
		$_SESSION["game_name"] = "BlackJack";

	}
}

//カードクラス
class Card{
	
	/**
	* 全てのトランプ
	*/
	private $All_tramp = array();
		
	function __construct(){
	
		$key = 0;
	 
		for($i = 1; $i<14;$i++){
			$this->All_tramp[$key] = "H:".$i;
			$key++;
			$this->All_tramp[$key] = "D:".$i;
			$key++;
			$this->All_tramp[$key] = "S:".$i;
			$key++;
			$this->All_tramp[$key] = "C:".$i;
			$key++;
		}
		
	}
	
/*	private $All_tramp = array(
		"H:1","H:2","H:3","H:4","H:5","H:6","H:7","H:8","H:9","H:10","H:11","H:12","H:13",
 -		"D:1","D:2","D:3","D:4","D:5","D:6","D:7","D:8","D:9","D:10","D:11","D:12","D:13",			
 -		"S:1","S:2","S:3","S:4","S:5","S:6","S:7","S:8","S:9","S:10","S:11","S:12","S:13",
 -		"C:1","C:2","C:3","C:4","C:5","C:6","C:7","C:8","C:9","C:10","C:11","C:12","C:13",
		);
	*/
							
	/**
	*トランプを配る二人用（一人に対して配る枚数,プレイヤー1、プレイヤー2）
	*/
	public function deal_tramp($now_use_tramp,$deal_tramp_count,$player1,$player2){
	
		for($i =0;$i <$deal_tramp_count;$i++){
			$now_use_tramp = $player1->hit($now_use_tramp); 
			$now_use_tramp = $player2->hit($now_use_tramp); 
		}
		return $now_use_tramp;

	}
	
	//表示側に渡す際に、絵柄のものは絵柄に変換
	public function display_card($array_card){
	
		$disp_card = array();
		foreach($array_card as $key => $val){
		
			//$valの値をマークと数字にわける
			$pieces = explode(":",$val);

			switch($pieces[0]){
				case "H":
					$mark = "♥"; break;
				case "D":
					$mark = "♦"; break;
				case "S":
					$mark = "♠"; break;
				case "C":
					$mark = "♣"; break;
			}
			
			switch($pieces[1]){
				case "11":
					$pieces[1] = "J"; break;
				case "12":
					$pieces[1] = "Q"; break;
				case "13":
					$pieces[1] = "K"; break;
				case "1":
					$pieces[1] = "A"; break;
			}
			$disp_card[$key] = $mark.":".$pieces[1];
		}
		
		return $disp_card;
	}
	
	//アクセサ
	public function get_All_tramp(){
		return $this->All_tramp;
	}
		
}

//プレイヤークラス
class Player{

	private $player_card = array();
	private $player_money = 1000;
	private $player_sum_card = 0;
	private $player_state = "hit";
	
	
	//カードを手札に一枚追加
	public function hit($now_use_tramp){
		//手札に追加
		array_push($this->player_card,reset($now_use_tramp));
		//ヤマにある札から配ったものを減らす
		array_shift($now_use_tramp);
		//現在のカードの合計を再計算し、セット
		$this->count_card_sum();
		//
		return $now_use_tramp;
	}
	
	
	//プレイヤーの現在のカードの合計を計算
	public function count_card_sum(){
	
		//
		$only_card_number_arr = array();
		
		//数字だけの配列に変換
		foreach($this->player_card as $val){
			$pieces = explode(":",$val);
			array_push($only_card_number_arr,$pieces[1]);
		}
		
		////合計値を出す
		$sum = 0;
		//まずは降順に並び替え
		rsort($only_card_number_arr);
		//まわす
		foreach($only_card_number_arr as $key => $val){
			
			//1(エース)が出るまではカードのスコアにより加点、1が出た場合は$sumの値により1か11でカウントするかを決定
			if($val >= 10){
				$sum += 10;
				
			}else if($val == 1){
				if($key != (count($only_card_number_arr)-1)){
					$sum += 1;
				}else{
					if($sum <= 10){
						$sum += 11;
					}else{
						$sum += 1;
					}
				}
			}else{
				$sum +=$val; 
			}
		}
		
		//合計値を返す
		$this->player_sum_card = $sum;
	}
		
	//親の行動
	public function parent_act($now_use_tramp){
	
		//親のカードが15以下だった場合、親はヒットする(条件は(仮))
		if($this->player_sum_card > 15){
			$this->player_state = "stand";
		}else{
			$now_use_tramp = $this->hit($now_use_tramp);
			//ヒットしたので、もう一度状態を確認
			if($this->player_sum_card > 15){
				$this->player_state = "stand";
			}
		}
		
		return $now_use_tramp;
	}
	
	//アクセサ
	public function set_player_card_key_value($key,$value){$this->player_card[$key] = $value;}
	public function set_player_card($array){$this->player_card = $array;}
	public function get_player_card() { return $this->player_card; }
	
	protected function set_player_sum_card($o) { $this->player_sum_card= $o; }
	public function get_player_sum_card() { return $this->player_sum_card; }

	protected function set_player_money($o) { $this->player_money= $o; }
	public function get_player_money() { return $this->player_money; }
	
	protected function set_player_state($o) { $this->player_state= $o; }
	public function get_player_state() { return $this->player_state; }

}


class Utility{
	
	//ブラックジャックで結果を出す処理
	public function result($player,$parent){
			
			//結果
			//引き分け条件
			if($player->get_player_sum_card() == $parent->get_player_sum_card() || ($parent->get_player_sum_card() > 21&&$player->get_player_sum_card() > 21)){
				$result="引き分け";
			}
			//プレイヤー勝利条件
			else if(($parent->get_player_sum_card() > 21)
			|| ($player->get_player_sum_card() > $parent->get_player_sum_card() && $player->get_player_sum_card() <= 21)){
				$result="あなたの勝ち";
			}
			//プレイヤー負け条件
			else if(($player->get_player_sum_card() > 21)
			|| ($player->get_player_sum_card() < $parent->get_player_sum_card() && $parent->get_player_sum_card() <= 21)){
				$result="あなたの負け";
			}
			
		return $result;
	}
	
	//表示側の共通処理(常にテンプレートに渡すもの)
	public function common_display($player1,$player2,$smarty){
			
		//	
		$card = new Card();	
		////表示側に渡す
		$smarty->set('game_name', 'BlackJack');
		$smarty->set('player_card', $card->display_card($player1->get_player_card()));
		$smarty->set('parent_card', $card->display_card($player2->get_player_card()));
		//行動を表示するかどうかのフラグを渡す
		$smarty->set('act_flg_ok', @$_SESSION['parent']);
	}
}
