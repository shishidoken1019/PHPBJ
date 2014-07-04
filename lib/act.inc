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
include("header.inc");

//ブラックジャックでヒットした場合
class Hit extends base_model {

	public function execute(){
		
		////初期処理
		include("header.inc");
		//インスタンスを作る
		$card = new card();
		$smarty = $this->get_conv();
		
		//ゲームをリロードしようとしたらエラー
		if(@$_SESSION['parent'] == null){
			//エラーページに飛ぶ
			header("Location: http://localhost/PHPBJ/wwwroot/error.html");
		}
		
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
				
		//もしプレイヤーのカードが21を超えていたら勝負
		if($player->get_player_sum_card() > 21){

			$result = $utility->result($player,$parent);
			
			//表示側に渡す
			$smarty->set('result',$result);
			$smarty->set("open", "open");
			$smarty->set('player_sum_card', $player->get_player_sum_card());
			$smarty->set('parent_sum_card', $parent->get_player_sum_card());
			
			//セッションを初期化
			unset($_SESSION['parent']); 
		}

		//表示側に毎回渡すものを渡す
		$utility->common_display($player,$parent,$smarty);
		
	}

}

//ブラックジャックでスタンドした場合
class Stand extends base_model {

	public function execute(){
		
		
		//ゲームをリロードしようとしたらエラー
		if(@$_SESSION['parent'] == null){
			//エラーページに飛ぶ
			header("Location: http://localhost/PHPBJ/wwwroot/error.html");
		}
		
		////初期処理
		include("header.inc");
		//インスタンスを作る
		$card = new card();
		$smarty = $this->get_conv();
	
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
		
		//もし親もスタンドの状態であれば勝負
		if($parent->get_player_state() == "stand"){
		
			//勝負の結果を持ってくる
			$result = $utility->result($player,$parent);
				
			//表示側に渡す
			$smarty->set('result',$result);
			$smarty->set("open", "open");
			$smarty->set('player_sum_card', $player->get_player_sum_card());
			$smarty->set('parent_sum_card', $parent->get_player_sum_card());
				
			//セッションを初期化
			unset($_SESSION['parent']); 
		}
		
		//表示側に毎回渡すものを渡す
		$utility->common_display($player,$parent,$smarty);
	}

}



