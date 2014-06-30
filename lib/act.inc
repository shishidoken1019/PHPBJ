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

//ブラックジャックでヒットした場合
class Hit extends base_model {

	public function execute(){
		//セッションから情報を取得
		$player = unserialize($_SESSION['player']);
		$parent = unserialize($_SESSION['parent']);
		$now_use_card = $_SESSION['now_use_card'];
		
		//親のカードが15以下だった場合、親はドロー(条件は(仮))
		if($parent)
		
		
		var_dump('dtete');
	}


}