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
{foreach from=$parent_card key=key item=var}
	{if $key == 0}
		<li>{$var}</li>
	{else}
		{if $open == "open" }
			<li>{$var}</li>
		{else}
			<li>■</li>
		{/if}
	{/if}
{/foreach}
</ul>

<h2>自分の手札</h2>
<ul>
{foreach from=$player_card item=var}
<li>{$var}</li>
{/foreach}
</ul>
{if $act_flg_ok != null}
<ul>
<li><a href="./index.php?c=hit">ヒット</a></li>
<li><a href="./index.php?c=stand">スタンド</a></li>
</ul>
{/if}

{if $result != null}
	<p><font color="red">{$result}</font></p>
	<p>あなたのカードの合計 : {$player_sum_card}</p>
	<p>親のカードの合計 : {$parent_sum_card}</p>
	<p><a href=./index.php?c=bj_start>継続してポーカーを遊ぶ</a></p>
	<p><a href=./index.php>ゲームを変更する</a></p>
{/if}
</body>
</html>