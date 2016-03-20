
//Tiempos
//Engrapadora
#define TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL unsigned long -1//Tiempo donde entran los ajsute del papel para el engrapado

#define TIM_ENTRADA_ENGRAPAR unsigned long -1//Tiempo donde se activa el mecanismo para engrapar
#define TIM_SIG_ENGRAPAR unsigned long -1//Tiempo que permanece la segnal de engrapado en el rele


#define TIM_ENTRADA_AVANCE_PAPEL_ENGRAPADORA unsigned long -1//Tiempo donde se activa el mecanismo avanzar el papel despues de ser engrapado
#define TIM_SIG_AVANCE_PAPEL_ENGRAPADORA unsigned long -1//Tiempo que permanece la segnal de avance del papel hacia la dobladora

//Dobladora
#define TIM_ENTRADA_TOPE_ENGRAPAR unsigned long -1//Tiempo donde se activa el tope para el engrape del papel, puede ser el mismo que TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL
#define TIM_SIG_TOPE_ENGRAPAR unsigned long -1//Tiempo que permanece la segnal del tope engrapado en el rele

#define TIM_ENTRADA_DOBLADORA unsigned long -1//Tiempo donde se activa la dobladora
#define TIM_SIG_DOBLADORA unsigned long -1//Tiempo que permanece la segnal de la dobladora en el rele

#define TIM_ENTRADA_SALIDA_CORRIENTE_DOBLADORA unsigned long -1//Tiempo donde se activa la salida de corriente para la salida del papel o la cortadora
#define TIM_SIG_DOBLADORA unsigned long -1//Tiempo que permanece la segnal de la salida de corriente en el rele