#ifndef MDAQ_H
#define MDAQ_H

#include <stdint.h>

#define APP_BUILD

#ifdef APP_BUILD
#define EXTERNC
#define MDAQ_API
#define SCI_MDAQ_API
#endif 

#ifdef DLL_BUILD
#define MDAQ_API __declspec(dllexport)
#define EXTERNC extern "C" 
#define SCI_MDAQ_API
#define SCI_EXTERNC
#endif 

#ifdef SCI_DLL_BUILD
#define SCI_EXTERNC extern "C" 
#define SCI_MDAQ_API __declspec(dllexport)
#define MDAQ_API
#define EXTERNC
#endif 

#ifdef __GNUC__
#define MDAQ_API extern
#define EXTERNC 
#endif 

#define OUT
#define IN
#define IO

EXTERNC MDAQ_API int mlink_connect(
		IN	const char 	*addr,		
		IN	uint16_t 	port,		
		OUT	int			*link);		

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
		IN	char 		data[], 
		IN	uint32_t 	len);

EXTERNC MDAQ_API int mlink_mem_get( 
		IO	int 		*link_fd, 
		IN	uint32_t 	addr, 
		IO	char 		data[], 
		IN	uint32_t 	len);

EXTERNC MDAQ_API int mlink_gpio_set_dir(
		IO	int 		*link_fd, 
		IN	uint8_t 	bank,
		IN	uint8_t 	pin,
		IN	uint8_t		dir );

EXTERNC MDAQ_API int mlink_gpio_open(
		IO	int 		*link_fd, 
		IN	uint8_t 	bank,
		IN	uint8_t 	pin,
		IN	uint8_t		dir,
		IN	uint8_t 	init_value); 

EXTERNC MDAQ_API int mlink_gpio_close(
		IO	int 		*link_fd, 
		IN	uint8_t 	bank,
		IN	uint8_t 	pin);

EXTERNC MDAQ_API int mlink_gpio_set(
		IO	int 		*link_fd, 
		IN	uint8_t 	bank,
		IN	uint8_t 	pin,
		IN	uint8_t 	value );

EXTERNC MDAQ_API int mlink_gpio_get(
		IO	int 		*link_fd, 
		IN	uint8_t 	bank,
		IN	uint8_t 	pin,
		OUT	uint8_t 	*value );

EXTERNC MDAQ_API int mlink_set_double( 
		IO	int		   *link_fd, 
		IN	char	   *var_name, 
		IN	double	 	value );

EXTERNC MDAQ_API int mlink_set_uint32( 
		IO	int		   *link_fd, 
		IN	char	   *var_name, 
		IN	uint32_t	value ); 

EXTERNC MDAQ_API int mlink_get_uint32( 
		IO	int			*link_fd, 
		IN	char		*var_name, 
		OUT	uint32_t	*value );

EXTERNC MDAQ_API int mlink_get_float( 
		IO	int			*link_fd, 
		IN	char	    *var_name, 
		OUT	float   	*value );

EXTERNC MDAQ_API int mlink_dsp_load( 
		IO	int			*link_fd, 
		IN	const char 	*dspapp, 
		IN	const char 	*param );

EXTERNC MDAQ_API int mlink_dsp_start(
		IO	int			*link_fd );

EXTERNC MDAQ_API int mlink_dsp_stop( 
		IO	int			*link_fd );

EXTERNC MDAQ_API int mlink_enc_get(
		IO	int 		*link_fd, 
		IN	uint8_t 	ch,
		OUT	int32_t		*value);

EXTERNC MDAQ_API int mlink_enc_reset(
		IO	int 		*link_fd, 
		IN	uint8_t 	ch );

EXTERNC MDAQ_API int mlink_pru_exec( 
		IO	int			*link_fd, 
		IN	const char 	*pru_fw, 
		IN	uint8_t 	pru_num );

EXTERNC MDAQ_API int mlink_pru_stop( 
		IO	int			*link_fd,
		IN	uint8_t 	pru_num );

EXTERNC MDAQ_API int mlink_pru_mem_set(
		IO	int 		*link_fd, 
		IN	uint8_t 	pru_num, 
		IN	uint32_t 	addr, 
		IN	char 		data[], 
		IN	uint32_t 	len);

EXTERNC MDAQ_API int mlink_pru_mem_get(
		IO	int 		*link_fd,
		IN	uint8_t 	pru_num, 
		IN	uint32_t 	addr, 
		IO	char 		data[], 
		IN	uint32_t 	len);

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

#endif /* MDAQ_H */ 
