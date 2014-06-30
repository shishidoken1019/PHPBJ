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
		if($_SESSION['parent'] == null){
			//エラーページに飛ぶ
		}
		
		//親のインスタンスを作る
		$parent = new Player();
		//プレイヤーのインスタンスを持ってくる
		$player = unserialize($_SESSION['player']);
	
		//ゲームを始めるにあたってトランプを作る
		$card = new Card();
		$now_use_tramp = $card->get_All_tramp();
		
		//トランプを混ぜる
		shuffle($now_use_tramp);
		
		//カードを親とプレイヤーに配る
		$card->deal_tramp($now_use_tramp,2,$parent,$player);
		
		//プレイヤーと親のカードを計算
		$parent->count_card_sum();
		$player->count_card_sum();
		
		//セッションに情報を格納
		$_SESSION['now_use_card'] = $now_use_tramp;
		$_SESSION['parent'] = serialize($parent);
		$_SESSION['player'] = serialize($player);
		
		 //表示側に渡す
		$smarty = $this->get_conv();
		$smarty->set('game_name', 'BlackJack');
		$smarty->set('player_card', $player->get_player_card());
		$smarty->set('parent_card', $parent->get_player_card());
		
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
							"H:1","H:2","H:3","H:4","H:5","H:6","H:7","H:8","H:9","H:10","H:11","H:12","H:13",
							"D:1","D:2","D:3","D:4","D:5","D:6","D:7","D:8","D:9","D:10","D:11","D:12","D:13",
							"S:1","S:2","S:3","S:4","S:5","S:6","S:7","S:8","S:9","S:10","S:11","S:12","S:13",
							"C:1","C:2","C:3","C:4","C:5","C:6","C:7","C:8","C:9","C:10","C:11","C:12","C:13",
							);
							
	/**
	*トランプを配る二人用（一人に対して配る枚数,プレイヤー1、プレイヤー2）
	*/
	public function deal_tramp($now_use_tramp,$deal_tramp_count,$player1,$player2){
		for($i =0;$i <($deal_tramp_count*2);$i++){
			//親のカード
			if($i%2 == 0){
				$player1->add_player_card($now_use_tramp[$i]); 
			//プレイヤーのカード	
			}else{
				$player2->add_player_card($now_use_tramp[$i]); 
			}
			//使われたカードはヤマから抜く
			unset($now_use_tramp[$i]);
		}

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
	
	//プレイヤーの手札にカードを追加
	public function add_player_card($c){
		array_push($this->player_card,$c);
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
		arsort($only_card_number_arr);
		var_dump($only_card_number_arr);
		//まわす
		foreach($only_card_number_arr as $key => $val){
//		var_dump($val);
			
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
		
		var_dump($sum);
		return $sum;

	}
	
	//ヒット（カードをもち札に追加)
	public function hit($use_now_card){
		$player->add_player_card($use_now_card);
	}
	
	//親の行動
	public function parent_act($now_use_card,$parent){
	
		//親のカードが15以下だった場合、親はドロー(条件は(仮))
		if($parent->count_card_sum() =< 15){
			$parent
		}
	}
	
	protected function set_player_card($o) { $this->player_card= $o; }
	public function get_player_card() { return $this->player_card; }
	
	protected function set_sum_card($o) { $this->sum_card= $o; }
	public function get_sum_card() { return $this->sum_card; }

	
	protected function set_player_money($o) { $this->player_money= $o; }
	public function get_player_money() { return $this->player_money; }
	

}
