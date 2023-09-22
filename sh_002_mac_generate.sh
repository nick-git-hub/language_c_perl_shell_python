#!/bin/bash
# (()) write   ==,   >， >=，  <， <=
# []   write  -eq，-gt，-ge，-lt，-le

macdec=$( printf "%d\n" 0x0C6714E36BEA );
counter=10;
add_number=8;
while [ "$counter" -gt 0 ] ; do
let counter--;
macdec=$( expr $macdec + $add_number );
machex=$( printf "%012X\n" $macdec );
printf "$machex\n" | sed -e 's/../&:/g' -e 's/:$//';
done

