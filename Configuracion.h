#ifndef Configuracion_h
#define Configuracion_h

//Tiempos
//Engrapadora
#define TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL 1100//Tiempo donde entran los ajsute del papel para el engrapado
#define MITAD_VUELTAS_AJUSTE_HORI_VERT_PAPEL 3//Numero de mitad de vueltas


#define TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL_DEJAR_PASAR 1900 //Tiempo dedpues de engrapar para relajar los ajuste de papel y dejar pasar el papel
#define MITAD_VUELTAS_AJUSTE_HORI_VERT_PAPEL_DEJAR_PASAR 1//Numero de mitad de vueltas


#define TIM_ENTRADA_ENGRAPAR 1600//Tiempo donde se activa el mecanismo para engrapar
#define TIM_SIG_ENGRAPAR 100//Tiempo que permanece la segnal de engrapado en el rele


#define TIM_ENTRADA_TOPE_ENGRAPAR 0//Tiempo donde se activa el tope para el engrape del papel, puede ser el mismo que TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL
#define TIM_SIG_TOPE_ENGRAPAR 1900//Tiempo que permanece la segnal del tope engrapado en el rele


#define TIM_ENTRADA_AVANCE_PAPEL_ENGRAPADORA 2200//Tiempo donde se activa el mecanismo avanzar el papel despues de ser engrapado
#define TIM_SIG_AVANCE_PAPEL_ENGRAPADORA 100//Tiempo que permanece la segnal de avance del papel hacia la dobladora

//Dobladora

#define TIM_ENTRADA_DOBLADORA 2900//Tiempo donde se activa la dobladora
#define TIM_SIG_DOBLADORA 64//Tiempo que permanece la segnal de la dobladora en el rele


#define TIM_ENTRADA_SALIDA_CORRIENTE_DOBLADORA 2900//Tiempo donde se activa la salida de corriente para la salida del papel o la cortadora
#define TIM_SIG_SALIDA_CORRIENTE_DOBLADORA  1000//Tiempo que permanece la segnal de la salida de corriente en el rele

//TORRE

#define TIM_FRECUENCIA_REVISAR_ENTRADA_PAPEL_TORRE 2000//Tiempo de la frecuencia para revisar la entrada de papel 400


#endif
