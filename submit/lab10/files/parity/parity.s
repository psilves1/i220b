	.text
	.globl get_parity
#edi contains n	
get_parity:
	#@TODO: add code here to set eax to 1 iff edi has even parity
	xor %eax, %eax
	testl %edi, %edi
	JPE .even
	ret
	
.even:
	xor $1, %eax
	ret
