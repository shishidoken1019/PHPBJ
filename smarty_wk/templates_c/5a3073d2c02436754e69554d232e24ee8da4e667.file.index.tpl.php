<?php /* Smarty version Smarty-3.1.18, created on 2014-06-27 15:37:50
         compiled from "C:\Program Files\Apache Software Foundation\Apache2.2\htdocs\PHPBJ\template\index.tpl" */ ?>
<?php /*%%SmartyHeaderCode:469453ad110aa464b4-11670995%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '5a3073d2c02436754e69554d232e24ee8da4e667' => 
    array (
      0 => 'C:\\Program Files\\Apache Software Foundation\\Apache2.2\\htdocs\\PHPBJ\\template\\index.tpl',
      1 => 1403851069,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '469453ad110aa464b4-11670995',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.18',
  'unifunc' => 'content_53ad110aaa0246_44295916',
  'variables' => 
  array (
    'message' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_53ad110aaa0246_44295916')) {function content_53ad110aaa0246_44295916($_smarty_tpl) {?><!DOCTYPE HTML>
<html lang="ja">
<head>
<meta charset="UTF-8">
<title>MagicWeapon HelloWorld.</title>
</head>
<body>
<?php echo $_smarty_tpl->tpl_vars['message']->value;?>


<p><a href="./index.php?c=bj_start">ブラックジャックを開始</a></p>
<p><a href="./index.php?c=poker_start">ポーカーを開始</a></p>

</body>
</html><?php }} ?>
