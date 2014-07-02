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
		
		//ゲームをリロードしようとしたらエラー
		if(@$_SESSION['parent'] != null){
		
			//セッションを消して
			unset($_SESSION['parent']);
			//エラーページに飛ぶ
			header("Location: http://localhost/PHPBJ/wwwroot/error.html");
		}
				
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
		//渡す前に親のカードを隠す分は隠す
		$smarty->set('game_name', 'BlackJack');
		$smarty->set('player_card', $player->get_player_card());
		$smarty->set('parent_card', $parent->get_player_card());
		$smarty->set('act_flg_ok', @$_SESSION['parent']);
				
	}
}


class Poker extends base_model{

	public function execute() {
		$conv = $this->get_conv();
		$conv->monoDic('game_name','ポーカー');
	}
}

//カードクラス
class Card{
	
	/**
	* 全てのトランプ
	*/
	private $All_tramp = array(
							"ハート:A","ハート:2","ハート:3","ハート:4","ハート:5","ハート:6","ハート:7","ハート:8","ハート:9","ハート:10","ハート:J","ハート:Q","ハート:K",
							"ダイヤ:A","ダイヤ:2","ダイヤ:3","ダイヤ:4","ダイヤ:5","ダイヤ:6","ダイヤ:7","ダイヤ:8","ダイヤ:9","ダイヤ:10","ダイヤ:J","ダイヤ:Q","ダイヤ:K",			
							"スペード:A","スペード:2","スペード:3","スペード:4","スペード:5","スペード:6","スペード:7","スペード:8","スペード:9","スペード:10","スペード:J","スペード:Q","スペード:K",
							"クローバー:A","クローバー:2","クローバー:3","クローバー:4","クローバー:5","クローバー:6","クローバー:7","クローバー:8","クローバー:9","クローバー:10","クローバー:J","クローバー:Q","クローバー:K",
							);
							
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
			if($val == 10 || $val == "J" || $val == "Q" || $val == "K"){
				$sum += 10;
				
			}else if($val == "A"){
			
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
