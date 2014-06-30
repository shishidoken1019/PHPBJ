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
	
	unset($_SESSION['player']);
	
		//プレイヤーのインスタンスを作る
		$player = new Player();
		
		
		$conv = $this->get_conv();
		$conv->monoDic('message', '仙台メディアテイク');
		$_SESSION['player'] = serialize($player);
  
  
	}

} // end of class
