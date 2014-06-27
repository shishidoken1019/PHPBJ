<?php /* Smarty version Smarty-3.1.18, created on 2014-06-27 14:44:04
         compiled from "C:\Program Files\Apache Software Foundation\Apache2.2\htdocs\PHPBJ\template\bj.tpl" */ ?>
<?php /*%%SmartyHeaderCode:1076053acf7eeb7c3a0-49300204%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '5f7004b2f1417aa68baadcbfde7770699533556a' => 
    array (
      0 => 'C:\\Program Files\\Apache Software Foundation\\Apache2.2\\htdocs\\PHPBJ\\template\\bj.tpl',
      1 => 1403847840,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '1076053acf7eeb7c3a0-49300204',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.18',
  'unifunc' => 'content_53acf7ef15a8e2_35078743',
  'variables' => 
  array (
    'game_name' => 0,
    'parent_card' => 0,
    'var' => 0,
    'player_card' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_53acf7ef15a8e2_35078743')) {function content_53acf7ef15a8e2_35078743($_smarty_tpl) {?><!DOCTYPE HTML>
<html lang="ja">
<head>
<meta charset="UTF-8">
<title>MagicWeapon HelloWorld.</title>
</head>
<body>
<h1><?php echo $_smarty_tpl->tpl_vars['game_name']->value;?>
</h1>

<h2>親の手札</h2>
<ul>
<?php  $_smarty_tpl->tpl_vars['var'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['var']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['parent_card']->value; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['var']->key => $_smarty_tpl->tpl_vars['var']->value) {
$_smarty_tpl->tpl_vars['var']->_loop = true;
?>
<li><?php echo $_smarty_tpl->tpl_vars['var']->value;?>
</li>
<?php } ?>
</ul>

<h2>自分の手札</h2>
<ul>
<?php  $_smarty_tpl->tpl_vars['var'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['var']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['player_card']->value; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['var']->key => $_smarty_tpl->tpl_vars['var']->value) {
$_smarty_tpl->tpl_vars['var']->_loop = true;
?>
<li><?php echo $_smarty_tpl->tpl_vars['var']->value;?>
</li>
<?php } ?>
</ul>

<ul>
<li><a href="./index.php?c=hit">ヒット</a></li>
<li><a href="./index.php?c=stand">スタンド</a></li>
</ul>
</body>
</html><?php }} ?>
