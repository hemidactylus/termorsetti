<html>
<head>
	<title>Termorsetti Local Page</title>
	<link rel="shortcut icon" href="images/orsetti_icon.gif" />

</head>
<body bgcolor="#b00040">
<div align="center"><img src="images/bear.gif" height="200px" style="vertical-align:middle"><br><font size="+3">TermOrsetti</font></div>
<p align="center">
    <table style="width:50%" border="2px">
    <tr>
        <th>Temp Outside</th>
        <th>Temp Inside</th>
        <th>Temp Inside (Dig)</th>
        <th>Rel. humidity (Dig)</th>
    </tr>
    <tr>
<td>
<?php
        $temp0=exec("cat /root/orsetti/t0");
        print "$temp0 &#8451;";
?></td>
<td>
<?php
        $temp1=exec("cat /root/orsetti/t1");
        print "$temp1 &#8451;";
?></td>
<td>
<?php
        $temp2=exec("cat /root/orsetti/t2");
        print "$temp2 &#8451;";
?></td>
<td>
<?php
        $humi0=exec("cat /root/orsetti/h0");
        print "$humi0 &#37;";
?></td>
    </tr>
    </table>
</p>
</body>
</html>
