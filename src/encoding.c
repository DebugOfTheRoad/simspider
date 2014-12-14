#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iconv.h"

#define MAXLEN_XMLCONTENT	100 * 1024

char *ConvertContentEncodingEx( char *encFrom , char *encTo , char *inptr , int *inptrlen , char *outptr , int *outptrlen )
{
	iconv_t		ic ;
	
	int		ori_outptrlen = 0 ;
	
	static char	outbuf[ MAXLEN_XMLCONTENT + 1 ]; /* ����û�û�з����ڴ棬��ʹ�þ�̬������ */
	size_t		outbuflen ; /* ��̬���������� */
	
	char		*pin = NULL ; /* �����ַ���ָ�� */
	size_t		inlen ; /* �����ַ������� */
	char		*pout = NULL ; /* ����ַ���ָ�� */
	size_t		*poutlen = NULL ; /* ����ַ������ȵ�ַ */
	
	int		nret ;
	
	/* ��iconv_t���� */
	ic = iconv_open( encTo , encFrom ) ;
	if( ic == (iconv_t)-1 )
	{
		 return NULL;
	}
	nret = iconv( ic , NULL , NULL , NULL , NULL ) ;
	
	/* �������ָ�븳ֵ */
	pin = inptr ;
	if( inptrlen )
	{
		inlen = (*inptrlen) ;
	}
	else
	{
		inlen = strlen((char*)inptr) + 1 ;
	}
	if( outptr )
	{
		memset( outptr , 0x00 , (*outptrlen) );
		if( inptr == NULL )
			return outptr;
		
		pout = outptr ;
		poutlen = (size_t*)outptrlen ;

		ori_outptrlen = (*outptrlen) ;
	}
	else
	{
		memset( outbuf , 0x00 , sizeof(outbuf) );
		outbuflen = MAXLEN_XMLCONTENT ;
		if( inptr == NULL )
			return outbuf;
		
		pout = outbuf ;
		poutlen = & outbuflen ;
	}
	
	/* ����ת�� */
	nret = iconv( ic , (char **) & pin , & inlen , (char **) & pout , poutlen );
	iconv_close( ic ); /* �ر�iconv_t���� */
	if( nret == -1)
		 return NULL;
	
	/* ���� */
	if( outptr )
	{
		(*outptrlen) = ori_outptrlen - (*poutlen) ;
		return pout - (*outptrlen) ;
	}
	else
	{
		return outbuf;
	}
}

char *ConvertContentEncoding( char *encFrom , char *encTo , char *inptr )
{
	return ConvertContentEncodingEx( encFrom , encTo , inptr , NULL , NULL , NULL );
}

