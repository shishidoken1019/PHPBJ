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

require_once('game.inc');

//セッションスタート
if( !isset($_SESSION) ) {
  session_start();
}

//必要なインスタンスを作る
$utility = new Utility();