<!DOCTYPE HTML>
<html lang="ja">
<head>
<meta charset="UTF-8">
<title>MagicWeapon HelloWorld.</title>
</head>
<body>
<h1>{$game_name}</h1>

<h2>親の手札</h2>
<ul>
{foreach from=$parent_card item=var}
<li>{$var}</li>
{/foreach}
</ul>

<h2>自分の手札</h2>
<ul>
{foreach from=$player_card item=var}
<li>{$var}</li>
{/foreach}
</ul>

<ul>
<li><a href="./index.php?c=hit">ヒット</a></li>
<li><a href="./index.php?c=stand">スタンド</a></li>
</ul>
</body>
</html>