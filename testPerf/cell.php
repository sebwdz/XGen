<?php
global $tab;

$tab = array();
$len = 100;
$val = 5;

for ($x = 0; $x < $len; $x++)
  BCL($x, $len, $val);

function BCL($x, $len, $val)
{
  global $tab;
  
  if (!isset($tab[$x]))
    $tab[$x] = array();
  $it = 0;
  while ($it < $len) {
    //    echo $x." ".$it."\n";
    $tab[$x][$it] = $val;
    $it++;
  }
}
?>
