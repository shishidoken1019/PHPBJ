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
require_once('game.inc');

//ブラックジャックでヒットした場合
class Hit extends base_model {

	

	public function execute(){
		
		//セッションから情報を取得
		$player = unserialize($_SESSION['player']);
		$parent = unserialize($_SESSION['parent']);
		$now_use_tramp = $_SESSION['now_use_tramp'];
	
		//親が行動
		$now_use_tramp = $parent->parent_act($now_use_tramp);
		
		//ヒットしたのでプレイヤーは手札にカードを追加
		$now_use_tramp = $player->hit($now_use_tramp);
		
		//セッションに情報をセットする
		$_SESSION['now_use_tramp'] = $now_use_tramp;
		$_SESSION['parent'] = serialize($parent);
		$_SESSION['player'] = serialize($player);
		
		//表示側に渡す
		$smarty = $this->get_conv();
		$smarty->set('game_name', 'BlackJack');
		$smarty->set('player_card', $player->get_player_card());
		$smarty->set('parent_card', $parent->get_player_card());
		
		//もしプレイヤーのカードが21を超えていたら勝負
		if($player->get_player_sum_card() > 21){
			//
			$utility = new Utility();
			$result = $utility->result_out($player,$parent);
			
			//表示側に渡す
			$smarty->set('result',$result);
			$smarty->set('player_sum_card', $player->get_player_sum_card());
			$smarty->set('parent_sum_card', $parent->get_player_sum_card());
		}
	}

}

//ブラックジャックでスタンドした場合
class Stand extends base_model {

	public function execute(){
	
		//セッションから情報を取得
		$player = unserialize($_SESSION['player']);
		$parent = unserialize($_SESSION['parent']);
		$now_use_tramp = $_SESSION['now_use_tramp'];
			
		//親が行動
		$now_use_tramp = $parent->parent_act($now_use_tramp);
		
		//プレイヤーの状態を書き換え
		$player->set_player_state = "stand";	
		
		//セッションに情報をセットする
		$_SESSION['now_use_tramp'] = $now_use_tramp;
		$_SESSION['parent'] = serialize($parent);
		$_SESSION['player'] = serialize($player);
		
		//表示側に渡す
		$smarty = $this->get_conv();
		$smarty->set('game_name', 'BlackJack');
		$smarty->set('player_card', $player->get_player_card());
		$smarty->set('parent_card', $parent->get_player_card());
		
		//もし親もスタンドの状態であれば勝負
		if($parent->get_player_state() == "stand"){
		
			//インスタンスを作る
			$utility = new Utility();
			$result = $utility->result_out($player,$parent);
			
			//表示側に渡す
			$smarty->set('result',$result);
			$smarty->set('player_sum_card', $player->get_player_sum_card());
			$smarty->set('parent_sum_card', $parent->get_player_sum_card());

		}
		
		
		
	}

}

class Utility{
	
	//ブラックジャックで結果を出す共通処理
	public function result_out($player,$parent){
			
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
}


