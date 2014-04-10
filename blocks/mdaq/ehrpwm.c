
#if (!defined MATLAB_MEX_FILE) && (!defined MDL_REF_SIM_TGT)
#include <stdio.h>
#include <stdint.h>

#include "utils.h"

/******************** Time base sub module*****************************/
#define TBCTL				0x0
#define TBSTS				0x2
#define TBPHS				0x6
#define TBCTR				0x8
#define TBPRD				0xA

#define TBCTL_CLKDIV_MASK		(BIT(12) | BIT(11) | BIT(10))
#define TBCTL_HSPCLKDIV_MASK	(BIT(9) | BIT(8) | BIT(7))
#define TBCTL_SYNCOSEL_MASK		(BIT(5) | BIT(4))
#define TBCTL_CTRMODE_MASK		(BIT(1) | BIT(0))

#define	TBCTL_CLKDIV_POS		0xA
#define TBCTL_HSPCLKDIV_POS		0x7
#define TBCTL_PHSEN_POS			0x2
#define TBCTL_SYNCOSEL_POS		0x4
#define TBCTL_PHSDIR_POS		0xD
#define TBCTL_FRC_SYC_POS		0x6
#define TBCTL_LOAD_MD_POS		0x3

#define TBCTL_FREERUN_FREE		0x2
#define TBCTL_CTRMOD_CTRUP		0x0

/******************* Counter-Compare Sub Module ***********************/
#define CMPCTL				0xE
#define CMPA				0x12
#define CMPB				0x14

#define CMPCTL_LDBMODE_MASK		(BIT(3) | BIT(2))
#define CMPCTL_LDAMODE_MASK		(BIT(1) | BIT(0))

#define CMPCTL_SHDAMODE_POS		0x4
#define CMPCTL_SHDBMODE_POS		0x6
#define CMPCTL_LDBMODE_POS		0x2

/*********************** Action Control Sub module ********************/
#define AQCTLA				0x16
#define AQCTLB				0x18
#define AQSFRC				0x1A
#define AQCSFRC				0x1c

#define ACTCTL_CBD_MASK			(BIT(11) | BIT(10))
#define ACTCTL_CBU_MASK			(BIT(9) | BIT(8))
#define ACTCTL_CAD_MASK			(BIT(7) | BIT(6))
#define ACTCTL_CAU_MASK			(BIT(5) | BIT(4))
#define ACTCTL_CPRD_MASK		(BIT(3) | BIT(2))
#define ACTCTL_CZRO_MASK		(BIT(1) | BIT(0))

#define ACTCTL_CTREQPRD_POS		0x2
#define ACTCTL_CTREQCMPAUP_POS		0x4
#define ACTCTL_CTREQCMPADN_POS		0x6
#define ACTCTL_CTREQCMPBUP_POS		0x8
#define ACTCTL_CTREQCMPBDN_POS		0xA

#define ACTCTL_CTREQCMP_LOW		0x1
#define ACTCTL_CTREQCMP_HIGH		0x2
#define ACTCTL_CTREQZRO_LOW		0x1
#define ACTCTL_CTREQZRO_HIGH		0x2

#define AQSFRC_ACTA_MASK		(BIT(1) | BIT(0))
#define AQSFRC_ACTB_MASK		(BIT(4) | BIT(3))
#define AQCSFRC_CFRC_LOAD_MASK		(BIT(7) | BIT(6))
#define AQCSFRC_OUTB_MASK		(BIT(3) | BIT(2))
#define AQCSFRC_OUTA_MASK		(BIT(1) | BIT(0))

#define AQSFRC_ACTB_POS			0x3
#define AQSFRC_OTFRCA_POS		0x2
#define AQSFRC_OTFRCB_POS		0x5
#define AQSFRC_LDMD_POS			0x6

#define AQCSFRC_OUTB_POS		0x2

/******************** Dead Band Generator Sub module *******************/
#define DBCTL				0x1E
#define DBRED				0x20
#define DBFED				0x22

#define DBCTL_INMODE_MASK		(BIT(5) | BIT(4))
#define DBCTL_PLSEL_MASK		(BIT(3) | BIT(2))
#define DBCTL_OUTMODE_MASK		(BIT(1) | BIT(0))

#define DBCTL_INMODE_POS		0x4
#define DBCTL_POLSEL_POS		0x2

/********************** PWM Chopper Sub module ************************/
#define PCCTL				0x3C

#define PCCTL_CHPDUTY_MASK		(BIT(10) | BIT(9) | BIT(8))
#define PCCTL_CHPFREQ_MASK		(BIT(7) | BIT(6) | BIT(5))
#define PCCTL_OSHTWTH_MASK		(BIT(4) | BIT(3) | BIT(2) | BIT(1))

#define PCCTL_CHPDUTY_POS		0x8
#define PCCTL_CHPFRQ_POS		0x5
#define PCCTL_OSTWID_POS		0x1

/*************************Trip-zone submodule **************************/
#define TZSEL				0x24
#define TZCTL				0x28
#define TZEINT				0x2A
#define TZFLG				0x2C
#define TZCLR				0x2E
#define TZFRC				0x30

#define TZCTL_ACTA_MASK			(BIT(1) | BIT(0))
#define TZCTL_ACTB_MASK			(BIT(3) | BIT(2))

#define TZCTL_ACTB_POS			0x2

#define TZEINT_OSHTEVT_POS		0x2
#define TZEINT_CBCEVT_POS		0x1

/*************************Event-Trigger submodule registers**************/
#define ETSEL				0x32
#define ETPS				0x34
#define ETFLG				0x36
#define ETCLR				0x38
#define ETFRC				0x3A

#define ETSEL_INTSEL_MASK		(BIT(2) | BIT(1) | BIT(0))
#define ETPS_INTCNT_MASK		(BIT(3) | BIT(2))
#define ETPS_INTPRD_MASK		(BIT(1) | BIT(0))

#define ETSEL_EN_INT_EN_POS		0x3

/**********************High Resolution Registers ********************/
#define TBPHSHR				0x4
#define CMPAHR				0x10
#define HRCNFG				0x1040

#define HRCNFG_EDGEMD_MASK		(BIT(1) | BIT(0))
#define HRCNFG_LDMD_POS			0x3
#define HRCNFG_CTLMD_POS		0x2

#define EPWM0_BASE 				(0x01F00000)
#define EPWM1_BASE 				(0x01F02000)
#define EPWM2_BASE 				(0x01F04000)

#define ENABLE					(1)
#define DISABLE					(0)

#define MSEC_PER_SEC	1000L
#define USEC_PER_SEC    1000000L
#define NSEC_PER_SEC    1000000000L

enum ehrpwm_module
{
	PWM0A = 0,
	PWM0B,
	PWM1A,
	PWM1B,
	PWM2A,
	PWM2B
};

enum tz_event {
    TZ_ONE_SHOT_EVENT = 0,
    TZ_CYCLE_BY_CYCLE,
    TZ_OSHT_CBC,
    TZ_DIS_EVT
};

enum polarity {
	ACTIVE_LOW,
	ACTIVE_HIGH
};

static uint16_t prescale_val;

static inline unsigned short ehrpwm_read(uint8_t module, uint16_t offset)
{
	uint32_t base_addr;
	if ( module < PWM1A)
		base_addr = EPWM0_BASE;
	else if ( module > PWM0B && module < PWM2A)
		base_addr = EPWM1_BASE;
	else
		base_addr = EPWM2_BASE;

	return raw_read16(base_addr + offset);
}

static inline void ehrpwm_write(uint8_t module, uint16_t offset, uint16_t val)
{
	uint32_t base_addr;
	if ( module < PWM1A)
		base_addr = EPWM0_BASE;
	else if ( module > PWM0B && module < PWM2A)
		base_addr = EPWM1_BASE;
	else
		base_addr = EPWM2_BASE;

	raw_write16(val, base_addr + offset);
}

static void ehrpwm_reg_config(uint8_t module, uint16_t offset, uint16_t val, uint16_t mask)
{
	unsigned short read_val;

	read_val = ehrpwm_read(module, offset);
	read_val = read_val & ~mask;
	read_val = read_val | val;
	ehrpwm_write(module, offset, read_val);
}


/* Time Base Module Configurations */
int ehrpwm_tb_set_prescalar_val(uint8_t module, unsigned char clkdiv,
	unsigned char hspclkdiv)
{

	if (clkdiv > 0x7 || hspclkdiv > 0x7)
		return -1;

	ehrpwm_reg_config(module, TBCTL, clkdiv << TBCTL_CLKDIV_POS,
		       TBCTL_CLKDIV_MASK);
	ehrpwm_reg_config(module, TBCTL, hspclkdiv << TBCTL_HSPCLKDIV_POS,
		       TBCTL_HSPCLKDIV_MASK);
	return 0;
}

int ehrpwm_tb_config_sync(uint8_t module, unsigned char phsen,
	unsigned char syncosel)
{
	if (phsen > 1 || syncosel > 0x3)
		return -1;

	ehrpwm_reg_config(module, TBCTL, phsen << TBCTL_PHSEN_POS, BIT(2));
	ehrpwm_reg_config(module, TBCTL, syncosel << TBCTL_SYNCOSEL_POS,
		       TBCTL_SYNCOSEL_MASK);
	return 0;
}

int ehrpwm_tb_set_counter_mode(uint8_t module, unsigned char ctrmode,
	       unsigned char phsdir)
{
	if (ctrmode > 0x3 || phsdir > 1)
		return -1;

	ehrpwm_reg_config(module, TBCTL, phsdir << TBCTL_PHSDIR_POS, BIT(13));
	ehrpwm_reg_config(module, TBCTL, ctrmode, TBCTL_CTRMODE_MASK);

	return 0;
}

int ehrpwm_tb_force_sync(uint8_t module)
{
	ehrpwm_reg_config(module, TBCTL, ENABLE << TBCTL_FRC_SYC_POS, BIT(6));
	return 0;
}


int ehrpwm_tb_set_periodload(uint8_t module, unsigned char loadmode)
{
	if (loadmode > 0x1)
		return -1;

	ehrpwm_reg_config(module, TBCTL, loadmode << TBCTL_LOAD_MD_POS, BIT(3));

	return 0;
}

int ehrpwm_tb_read_status(uint8_t module, unsigned short *val)
{
	*val = ehrpwm_read(module, TBSTS);

	return 0;
}


int ehrpwm_tb_read_counter(uint8_t module, unsigned short *val)
{
	*val = ehrpwm_read(module, TBCTR);
	return 0;
}


int ehrpwm_tb_set_period(uint8_t module, unsigned short val)
{
	ehrpwm_write(module, TBPRD, val);
	return 0;
}


int ehrpwm_tb_set_phase(uint8_t module, unsigned short val)
{
	ehrpwm_write(module, TBPHS, val);
	return 0;
}

int ehrpwm_cmp_set_cmp_ctl(uint8_t module, unsigned char shdwamode,
	unsigned char shdwbmode, unsigned char loadamode,
	unsigned char loadbmode)
{
	if (shdwamode > 0x1 || shdwbmode > 0x1 || loadamode > 0x3 ||
		loadbmode > 0x3)
		return -1;

	ehrpwm_reg_config(module, CMPCTL, shdwamode << CMPCTL_SHDAMODE_POS,
		       BIT(4));
	ehrpwm_reg_config(module, CMPCTL, shdwbmode << CMPCTL_SHDBMODE_POS,
		       BIT(6));
	ehrpwm_reg_config(module, CMPCTL, loadamode, CMPCTL_LDAMODE_MASK);
	ehrpwm_reg_config(module, CMPCTL, loadbmode << CMPCTL_LDBMODE_POS,
		       CMPCTL_LDBMODE_MASK);

	return 0;
}

int ehrpwm_cmp_set_cmp_val(uint8_t module, unsigned char reg,
	unsigned short val)
{
	unsigned char offset;

	if (reg > 0x1)
		return -1;

	if (reg == 0)
		offset = CMPA;
	else
		offset = CMPB;

	ehrpwm_write(module, offset, val);

	return 0;
}

#if 0
int ehrpwm_aq_set_act_ctrl(uint8_t module, struct aq_config_params *cfg)
{
	unsigned char reg;

	if (!cfg)
		return -1;

	if (cfg->ch > 1 || cfg->ctreqzro > 3 || cfg->ctreqprd > 3 ||
		cfg->ctreqcmpaup > 3 || cfg->ctreqcmpadown > 3 ||
		cfg->ctreqcmpbup > 3 || cfg->ctreqcmpbdown > 3)
		return -1;

	if (cfg->ch == 0)
		reg = AQCTLA;
	else
		reg = AQCTLB;

	ehrpwm_reg_config(module, reg, cfg->ctreqzro, ACTCTL_CZRO_MASK);
	ehrpwm_reg_config(module, reg, cfg->ctreqprd << ACTCTL_CTREQPRD_POS,
		       ACTCTL_CPRD_MASK);
	ehrpwm_reg_config(module, reg, cfg->ctreqcmpaup <<
		       ACTCTL_CTREQCMPAUP_POS, ACTCTL_CAU_MASK);
	ehrpwm_reg_config(module, reg, cfg->ctreqcmpadown <<
		       ACTCTL_CTREQCMPADN_POS, ACTCTL_CAD_MASK);
	ehrpwm_reg_config(module, reg, cfg->ctreqcmpbup <<
		       ACTCTL_CTREQCMPBUP_POS, ACTCTL_CBU_MASK);
	ehrpwm_reg_config(module, reg, cfg->ctreqcmpbdown <<
		       ACTCTL_CTREQCMPBDN_POS, ACTCTL_CBD_MASK);

	return 0;
}
#endif

int ehrpwm_aq_set_one_shot_act(uint8_t module, unsigned char ch,
	unsigned char act)
{

	if (ch > 1 || act > 3)
		return -1;

	if (ch == 0)
		ehrpwm_reg_config(module, AQSFRC, act, AQSFRC_ACTA_MASK);
	else
		ehrpwm_reg_config(module, AQSFRC, act << AQSFRC_ACTB_POS,
			       AQSFRC_ACTB_MASK);

	return 0;
}


int ehrpwm_aq_ot_frc(uint8_t module, unsigned char ch)
{


	if (ch > 1)
		return -1;

	if (ch == 0)
		ehrpwm_reg_config(module, AQSFRC, ENABLE << AQSFRC_OTFRCA_POS,
			       BIT(2));
	else
		ehrpwm_reg_config(module, AQSFRC, ENABLE << AQSFRC_OTFRCB_POS,
			       BIT(5));

	return 0;
}


int ehrpwm_aq_set_csfrc_load_mode(uint8_t module, unsigned char loadmode)
{


	if (loadmode > 0x3)
		return -1;

	ehrpwm_reg_config(module, AQSFRC, loadmode << AQSFRC_LDMD_POS,
		       AQCSFRC_CFRC_LOAD_MASK);

	return 0;
}


int ehrpwm_aq_continuous_frc(uint8_t module, unsigned char ch,
	unsigned char act)
{


	if (ch > 1)
		return -1;

	if (ch == 0)
		ehrpwm_reg_config(module, AQCSFRC, act, AQCSFRC_OUTA_MASK);
	else
		ehrpwm_reg_config(module, AQCSFRC, act << AQCSFRC_OUTB_POS,
			       AQCSFRC_OUTB_MASK);

	return 0;
}

#if 0
int ehrpwm_db_get_max_delay(uint8_t module, enum config_mask cfgmask,
	unsigned long *delay_val)
{

	unsigned long delay_ns;
	unsigned long max_ticks;

	if (cfgmask == CONFIG_NS) {
		max_ticks = 0x3ff * prescale_val;
		delay_ns = pwm_ticks_to_ns(p, max_ticks);
		*delay_val = delay_ns;
	} else if (cfgmask == CONFIG_TICKS) {
		*delay_val = 0x3ff * prescale_val;
	} else {
		return -1;
	}

	return 0;
}


int ehrpwm_db_get_delay(uint8_t module, unsigned char edge,
	enum config_mask cfgmask, unsigned long *delay_val)
{

	unsigned long delay_ns;
	unsigned long delay_ticks;
	unsigned char offset;

	if (!module)
		return -1;

	if (edge == RISING_EDGE_DELAY)
		offset = DBRED;
	else if (edge == FALLING_EDGE_DELAY)
		offset = DBFED;
	else
		return -1;

	delay_ticks = ehrpwm_read(module, offset);
	/* Only least 10 bits are required */
	delay_ticks = delay_ticks & 0x3ff;
	if (cfgmask == CONFIG_TICKS) {
		*delay_val = delay_ticks * prescale_val;
	} else if (cfgmask == CONFIG_NS) {
		delay_ticks = delay_ticks * prescale_val;
		delay_ns = pwm_ticks_to_ns(p, delay_ticks);
		debug("\n delay ns value is %lu", delay_ns);
		*delay_val = delay_ns;
	} else {
		return -1;
	}

	return 0;
}
EXPORT_SYMBOL(ehrpwm_db_get_delay);

int ehrpwm_db_set_delay(uint8_t module, unsigned char edge,
		enum config_mask cfgmask, unsigned long delay)
{

	unsigned long delay_ticks;
	unsigned char offset = 0;

	if (!module)
		return -1;

	if (edge == RISING_EDGE_DELAY)
		offset = DBRED;
	else if (edge == FALLING_EDGE_DELAY)
		offset = DBFED;
	else
		return -1;

	if (cfgmask == CONFIG_TICKS) {
		delay = delay / prescale_val;
		if (delay > 0x3ff)
			return -1;
		ehrpwm_write(module, offset, delay);
	} else if (cfgmask == CONFIG_NS) {
		delay_ticks = pwm_ns_to_ticks(p, delay);
		delay_ticks = delay_ticks / prescale_val;
		if (delay_ticks > 0x3ff) {
			ehrpwm_db_get_max_delay(p, CONFIG_NS, &delay_ticks);
			dev_dbg(p->dev, "%s: Expected delay cannot be"
			" attained setting the maximum possible delay of"
			" %lu ns", __func__, delay_ticks);
			delay_ticks = 0x3ff;
		}
		debug("\n delay ticks is %lu", delay_ticks);
		ehrpwm_write(module, offset, delay_ticks);
	} else {
		return -1;
	}

	return 0;
}
#endif

/* Dead Band Configuration functions */
int ehrpwm_db_set_mode(uint8_t module, unsigned char inmode,
		unsigned char polsel, unsigned char outmode)
{


	if (inmode > 0x3 || polsel > 0x3 || outmode > 0x3)
		return -1;

	ehrpwm_reg_config(module, DBCTL, inmode << DBCTL_INMODE_POS,
		       DBCTL_INMODE_MASK);
	ehrpwm_reg_config(module, DBCTL, polsel << DBCTL_POLSEL_POS,
		       DBCTL_PLSEL_MASK);
	ehrpwm_reg_config(module, DBCTL, outmode, DBCTL_OUTMODE_MASK);

	return 0;
}


/* PWM chopper Configuration functions */
int ehrpwm_pc_configure(uint8_t module, unsigned char chpduty,
		unsigned char chpfreq, unsigned char oshtwidth)
{
	if (chpduty > 0x7 || chpfreq > 0x7 || oshtwidth > 0xf)
		return -1;

	ehrpwm_reg_config(module, PCCTL, chpduty << PCCTL_CHPDUTY_POS,
		       PCCTL_CHPDUTY_MASK);
	ehrpwm_reg_config(module, PCCTL, chpfreq << PCCTL_CHPFRQ_POS,
		       PCCTL_CHPFREQ_MASK);
	ehrpwm_reg_config(module, PCCTL, oshtwidth << PCCTL_OSTWID_POS,
		       PCCTL_OSHTWTH_MASK);

	return 0;
}


int ehrpwm_pc_en_dis(uint8_t module, unsigned char chpen)
{
	if (chpen > 1)
		return -1;

	ehrpwm_reg_config(module, PCCTL, chpen, BIT(0));

	return 0;
}

/* Trip Zone configuration functions */
int ehrpwm_tz_sel_event(uint8_t module, unsigned char input,
	       enum tz_event evt)
{
	unsigned short val = 0;
	unsigned short mask;
	unsigned short pos;

	if (evt > 4 || input > 7)
		return -1;

	switch (evt) {
	case TZ_ONE_SHOT_EVENT:
		pos = input + 8;
		mask = BIT((pos)) | BIT(input);
		ehrpwm_reg_config(module, TZSEL, 1 << pos, mask);
		break;

	case TZ_CYCLE_BY_CYCLE:
		pos = input;
		mask = BIT(pos) | BIT((pos + 8));
		ehrpwm_reg_config(module, TZSEL, 1 << pos, mask);
		break;

	case TZ_OSHT_CBC:
	case TZ_DIS_EVT:
		if (evt == TZ_OSHT_CBC)
			val = 1;
		else
			val = 0;

		pos = input + 8;
		mask = BIT((pos));
		ehrpwm_reg_config(module, TZSEL, val << pos, mask);
		pos = input;
		mask = BIT((pos));
		ehrpwm_reg_config(module, TZSEL, val << pos, mask);
		break;

	default:
		return -1;
	}
	return 0;
}


int ehrpwm_tz_set_action(uint8_t module, unsigned char ch,
	unsigned char act)
{
	if (act > 0x3 || ch > 1)
		return -1;

	if (ch == 0)
		ehrpwm_reg_config(module, TZCTL, act, TZCTL_ACTA_MASK);
	else
		ehrpwm_reg_config(module, TZCTL, act << TZCTL_ACTB_POS,
			       TZCTL_ACTB_MASK);

	return 0;
}

int ehrpwm_tz_set_int_en_dis(uint8_t module, enum tz_event event,
		unsigned char int_en_dis)
{
	if (event == TZ_ONE_SHOT_EVENT)
		ehrpwm_reg_config(module, TZEINT, int_en_dis <<
			       TZEINT_OSHTEVT_POS, BIT(2));
	else if (event == TZ_CYCLE_BY_CYCLE)
		ehrpwm_reg_config(module, TZEINT, int_en_dis <<
			       TZEINT_CBCEVT_POS, BIT(1));
	else
		return -1;

	return 0;
}


int ehrpwm_tz_force_evt(uint8_t module, enum tz_event event)
{
	if (event == TZ_ONE_SHOT_EVENT)
		ehrpwm_write(module, TZFRC, 0x4);
	else if (event == TZ_CYCLE_BY_CYCLE)
		ehrpwm_write(module, TZFRC, 0x2);
	else
		return -1;

	return 0;
}


inline int ehrpwm_tz_read_status(uint8_t module, unsigned short *status)
{
	*status = ehrpwm_read(module, TZFLG);

	return 0;
}


inline int ehrpwm_tz_clr_evt_status(uint8_t module)
{

	unsigned short ret;

	ret = ehrpwm_read(module, TZFLG);
	ehrpwm_write(module, TZCLR, ret & ~0x1);

	return 0;
}


inline int ehrpwm_tz_clr_int_status(uint8_t module)
{
	ehrpwm_write(module, TZCLR, 0x1);
	return 0;
}


/* Event Trigger Configuration functions */
int ehrpwm_et_set_sel_evt(uint8_t module, unsigned char evt,
		unsigned char prd)
{


	if (evt > 0x7 || prd > 0x3)
		return -1;

	ehrpwm_reg_config(module, ETSEL, evt, ETSEL_INTSEL_MASK);
	ehrpwm_reg_config(module, ETPS, prd, ETPS_INTPRD_MASK);

	return 0;
}


inline int ehrpwm_et_int_en_dis(uint8_t module, unsigned char en_dis)
{


	ehrpwm_reg_config(module, ETSEL, en_dis << ETSEL_EN_INT_EN_POS, BIT(3));

	return 0;
}


inline int ehrpwm_et_read_evt_cnt(uint8_t module,
	unsigned long *evtcnt)
{


	*evtcnt = ehrpwm_read(module, ETPS) & ETPS_INTCNT_MASK;
	*evtcnt >>= 0x2;

	return 0;
}


inline int ehrpwm_et_read_int_status(uint8_t module,
	unsigned long *status)
{


	*status = ehrpwm_read(module, ETFLG) & BIT(0);

	return 0;
}


inline int ehrpwm_et_frc_int(uint8_t module)
{


	ehrpwm_write(module, ETFRC, ENABLE);

	return 0;
}


inline int ehrpwm_et_clr_int(uint8_t module)
{


	ehrpwm_write(module, ETCLR, ENABLE);

	return 0;
}


/* High Resolution Module configuration */
inline int ehrpwm_hr_set_phase(uint8_t module, unsigned char val)
{
	ehrpwm_write(module, TBPHSHR, val << 8);

	return 0;
}


inline int ehrpwm_hr_set_cmpval(uint8_t module, unsigned char val)
{


	ehrpwm_write(module, CMPAHR, val << 8);

	return 0;
}


int ehrpwm_hr_config(uint8_t module, unsigned char loadmode,
		unsigned char ctlmode, unsigned char edgemode)
{
	if (loadmode > 1 || ctlmode > 1 || edgemode > 3)
		return -1;

	ehrpwm_reg_config(module, (uint16_t)HRCNFG, loadmode << HRCNFG_LDMD_POS, BIT(3));
	ehrpwm_reg_config(module, (uint16_t)HRCNFG, ctlmode << HRCNFG_CTLMD_POS, BIT(2));
	ehrpwm_reg_config(module, (uint16_t)HRCNFG, edgemode, HRCNFG_EDGEMD_MASK);

	return 0;
}


inline int ehrpwm_reg_read(uint8_t module, unsigned int reg,
	       unsigned short *val)
{
	if (reg > HRCNFG)
		return -1;

	*val = ehrpwm_read(module, reg);

	return 0;
}


inline int ehrpwm_reg_write(uint8_t module, unsigned int reg,
	       unsigned short val)
{
	if (reg > HRCNFG)
		return -1;

	ehrpwm_write(module, reg, val);

	return 0;
}


int ehrpwm_pwm_start(uint8_t module)
{
	unsigned short val;
	unsigned short read_val1;
	unsigned short read_val2;
	int chan;

	chan = module & 0x1;
	val = ehrpwm_read(module, TBCTL);
	val = (val & ~TBCTL_CTRMODE_MASK) | (TBCTL_CTRMOD_CTRUP |
		 TBCTL_FREERUN_FREE << 14);
	ehrpwm_write(module, TBCTL, val);

	ehrpwm_tz_set_action(module, chan, 0x3);
	read_val1 = ehrpwm_read(module, TZFLG);
	read_val2 = ehrpwm_read(module, TZCTL);
	/*
	 * State of the other channel is determined by reading the
	 * TZCTL register. If the other channel is also in running state,
	 * one shot event status is cleared, otherwise one shot action for
	 * this channel is set to "DO NOTHING.
	 */
	read_val2 = read_val2 & (chan ? 0x3 : (0x3 << 2));
	read_val2 = chan ? read_val2 : (read_val2 >> 2);

	if (!(read_val1 & 0x4) || (read_val2 == 0x3))
		ehrpwm_tz_clr_evt_status(module);

	return 0;
}

/*
 * Stop function is implemented using the Trip Zone module. Action for the
 * corresponding channel is set to low and the one shot software force
 * event is triggered.
 */
int ehrpwm_pwm_stop(uint8_t module)
{

	unsigned short read_val;
	int chan;

	chan = module & 0x1;

	/* Set the Trip Zone Action to low */
	ehrpwm_tz_set_action(module, chan, 0x2);

	read_val = ehrpwm_read(module, TZFLG);
	/*
	 * If the channel is already in stop state, Trip Zone software force is
	 * not required
	 */

	if (!(read_val & 0x4)) {
		ehrpwm_tz_clr_evt_status(module);
		ehrpwm_tz_force_evt(module, TZ_ONE_SHOT_EVENT);
	}

	return 0;
}

int ehrpwm_pwm_set_pol(uint8_t module, uint8_t polarity)
{
	unsigned int act_ctrl_reg;
	unsigned int ctreqcmp;
	unsigned short val;

	int chan = module & 0x1;

	if (!chan) {
		act_ctrl_reg = AQCTLA;
		ctreqcmp = 4;
	} else {
		act_ctrl_reg = AQCTLB;
		ctreqcmp = 8;
	}

	val = ((polarity ? ACTCTL_CTREQCMP_HIGH : ACTCTL_CTREQCMP_LOW)
		 << ctreqcmp) | (polarity ? ACTCTL_CTREQZRO_LOW :
			ACTCTL_CTREQZRO_HIGH);
	ehrpwm_write(module, act_ctrl_reg, val);

	return 0;
}

/*
 * Prescalar is used when the period value exceeds the maximum value
 * of the 16 bit period register. We always look for the minimum prescalar
 * value as it would result in wide range of duty control
 */
static char get_divider_val(unsigned int desired_ps_val, unsigned int
*ps_div_val, unsigned int *tb_div_val)
{
	char i = 0;
	char j = 0;

	for (i = 0; i <= 7; i++) {
		for (j = 0; j <= 7; j++) {
			if (((1 << i) * (j ? (j * 2) : 1)) >= desired_ps_val) {
				*ps_div_val = (1 << i) * (j ? (j * 2) : 1);
				*tb_div_val = (i << 10) | (j << 7) ;
				return 0;
			}
		}
	}

	return -1;
}

int ehrpwm_pwm_set_prd(uint8_t module, uint32_t period, uint8_t polarity)
{
	unsigned int ps_div_val = 1;
	unsigned int tb_div_val = 0;
	char ret;
	unsigned short val;
	unsigned short period_ticks;

	if (period > 65535) {
		ret = get_divider_val(period / 65535 + 1, &ps_div_val,
				&tb_div_val);
		if (ret) {
			return -1;
		}
	}


	val = ehrpwm_read(module, TBCTL);
	val = (val & ~TBCTL_CLKDIV_MASK & ~TBCTL_HSPCLKDIV_MASK) | tb_div_val;
	ehrpwm_write(module, TBCTL, val);

	// ehrpwm_tb_set_prescalar_val(module, 1 , 1);

	period_ticks = period / ps_div_val;

	if (period_ticks <= 1) {
		return -1;
	}

	/*
	 * Program the period register with 1 less than the actual value since
	 * the module generates waveform with period always 1 greater
	 * the programmed value.
	 */

	ehrpwm_pwm_set_pol(module, polarity);
	ehrpwm_write(module, TBPRD, (unsigned short)(period_ticks - 1));
	prescale_val = ps_div_val;

	return 0;
}

int ehrpwm_hr_duty_config(uint8_t module, uint16_t tick_hz, uint32_t duty_ns)
{
	unsigned char no_of_mepsteps;
	unsigned short cmphr_val;

	if (!tick_hz) {
		return -1;
	}

	/*
	 * Calculate the no of MEP steps. Assume system clock
	 * is in the order of MHZ.
	 */

	no_of_mepsteps = USEC_PER_SEC / ((tick_hz / USEC_PER_SEC) * 63);
	/* Calculate the CMPHR Value */
	cmphr_val = tick_hz / USEC_PER_SEC;
	cmphr_val = (duty_ns * cmphr_val) % MSEC_PER_SEC;
	cmphr_val = (cmphr_val * no_of_mepsteps) / 1000;
	cmphr_val = (cmphr_val << 8) + 0x180;
	ehrpwm_write(module, CMPAHR, cmphr_val);
	ehrpwm_write(module, HRCNFG, 0x2);

	return 0;
}

int ehrpwm_pwm_set_dty(uint8_t module, uint32_t duty)
{
	unsigned short duty_ticks = 0;

	int ret = 0;
	int chan;

	chan = module & 0x1;
	if (!prescale_val) {
		return -1;
	}

	duty_ticks = duty / prescale_val;

	/* High resolution module */
	if (chan && prescale_val <= 1) {
		/* TODO: check parameters */
		ret = ehrpwm_hr_duty_config(module, duty_ticks, duty);
		ehrpwm_write(module, HRCNFG, 0x2);
	}

	ehrpwm_write(module, (chan ? CMPB : CMPA), duty_ticks);

	return ret;
}
#endif 

