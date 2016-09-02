{
  "temp_ext": <?php     $temp0=exec("cat /root/orsetti/t0"); echo $temp0;  ?>,
  "temp_int": <?php     $temp1=exec("cat /root/orsetti/t1"); echo $temp1;  ?>,
  "temp_int_dig": <?php $temp2=exec("cat /root/orsetti/t2"); echo $temp2;  ?>,
  "humidity": <?php     $humi0=exec("cat /root/orsetti/h0"); echo $humi0;  ?>,
  "heatindex": <?php    $heat0=exec("cat /root/orsetti/hi"); echo $heat0;  ?>,
  "date": <?php         $date=exec("cat  /root/orsetti/last_date"); echo "\"$date\""; ?>
}

