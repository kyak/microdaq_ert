/*
 * Copyright 2013-2014 Embedded Solutions
 *
 * File: MLink.h     $Revision: 1.0.2 $
 *
 * Abstract:
 *	MLink function prototypes
 */

#ifndef MLINK_H
#define MLINK_H

#include <stdint.h>

#define OUT
#define IN
#define IO

#define EXTERNC
#define MDAQ_API

EXTERNC MDAQ_API char *mlink_error( int err );

EXTERNC MDAQ_API char *mlink_version( 
		IO	int 		*link_fd);

EXTERNC MDAQ_API int mlink_connect(
		IN	const char 	*addr,		
		IN	uint16_t 	port,		
		OUT	int		*link);		

EXTERNC MDAQ_API int mlink_disconnect( 
		IN 	int 		link );		

EXTERNC MDAQ_API int mlink_mem_open(
		IO	int 		*link_fd, 
		IN	uint32_t 	addr, 
		IN	uint32_t 	len);

EXTERNC MDAQ_API int mlink_mem_close(
		IO	int 		*link_fd, 
		IN	uint32_t 	addr, 
		IN	uint32_t 	len);

EXTERNC MDAQ_API int mlink_mem_set(
		IO	int 		*link_fd, 
		IN	uint32_t 	addr, 
		IN	int8_t 		*data, 
		IN	uint32_t 	len);

EXTERNC MDAQ_API int mlink_mem_get( 
		IO	int 		*link_fd, 
		IN	uint32_t 	addr, 
		IO	int8_t 		*data, 
		IN	uint32_t 	len);

EXTERNC MDAQ_API int mlink_dsp_load( 
		IO	int		*link_fd, 
		IN	const char 	*dspapp, 
		IN	const char 	*param );

EXTERNC MDAQ_API int mlink_dsp_start(
		IO	int		*link_fd );

EXTERNC MDAQ_API int mlink_dsp_stop( 
		IO	int		*link_fd );

EXTERNC MDAQ_API int mlink_dsp_upload( 
		IO	int		*link_fd ); 


EXTERNC MDAQ_API int mlink_get_obj_size(
		IO	int		*link_fd, 
		IN	char		*var_name,
		OUT	uint32_t	*size);

EXTERNC MDAQ_API int mlink_get_obj( 
		IO	int		*link_fd, 
		IN	char		*obj_name, 
		IO	void 		*data, 
		IN	uint32_t	size);

EXTERNC MDAQ_API int mlink_set_obj( 
		IO	int		*link_fd, 
		IN	char		*obj_name, 
		IN	void 		*data, 
		IN	uint32_t	size);

EXTERNC MDAQ_API int mlink_enc_get(
		IO	int 		*link_fd, 
		IN	uint8_t 	ch,
		OUT	int32_t		*value);

EXTERNC MDAQ_API int mlink_enc_reset(
		IO	int 		*link_fd, 
		IN	uint8_t 	ch );

EXTERNC MDAQ_API int mlink_pru_exec( 
		IO	int		*link_fd, 
		IN	const char 	*pru_fw, 
		IN	uint8_t 	pru_num );

EXTERNC MDAQ_API int mlink_pru_stop( 
		IO	int		*link_fd,
		IN	uint8_t 	pru_num );

EXTERNC MDAQ_API int mlink_pru_mem_set(
		IO	int 		*link_fd, 
		IN	uint8_t 	pru_num, 
		IN	uint32_t 	addr, 
		IN	uint8_t 	data[], 
		IN	uint32_t 	len);

EXTERNC MDAQ_API int mlink_pru_mem_get(
		IO		int 		*link_fd, 
		IN		uint8_t 	pru_num,
		IN		uint32_t 	addr, 
		IO		char 		data[], 
		IN		uint32_t 	len);

EXTERNC MDAQ_API int mlink_pru_reg_get( 
		IO	int			*link_fd,
		IN	uint8_t 	pru_num, 
		IN	uint8_t 	reg, 
		OUT	uint32_t	*reg_value);

EXTERNC MDAQ_API int mlink_pru_reg_set( 
		IO	int			*link_fd,
		IN	uint8_t 	pru_num, 
		IN	uint8_t 	reg, 
		IN	uint32_t	reg_value);


#endif /* MLINK_H */ 
