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
class Hit extends base_model {

	public function execute(){
		//セッションから情報を取得
		$player = unserialize($_SESSION['player']);
		$parent_card = $_SESSION['parent_card'];
		$now_use_card = $_SESSION['now_use_card'];
		
		//親のカードが15以下だった場合、親はドロー(条件は()仮)
		if()
		
		
		var_dump('dtete');
	}


}