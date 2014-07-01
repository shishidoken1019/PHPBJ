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


class mw_index extends base_model {

	//初期アクセス
	public function execute() {
	
		////初期処理
		unset($_SESSION['parent']); 
		unset($_SESSION['player']);
		//プレイヤーのインスタンスを作って、セッションに格納
		$player = new Player();
		$_SESSION['player'] = serialize($player);
  
  
	}

} // end of class
