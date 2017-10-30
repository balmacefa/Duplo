#ifndef Configuracion_h
#define Configuracion_h

//Tiempos
//Engrapadora
#define TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL 1000//Tiempo donde entran los ajsute del papel para el engrapado
#define MITAD_VUELTAS_AJUSTE_HORI_VERT_PAPEL 3//Numero de mitad de vueltas


#define TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL_DEJAR_PASAR 3000 //Tiempo dedpues de engrapar para relajar los ajuste de papel y dejar pasar el papel
#define MITAD_VUELTAS_AJUSTE_HORI_VERT_PAPEL_DEJAR_PASAR 1//Numero de mitad de vueltas


#define TIM_ENTRADA_ENGRAPAR 1000//Tiempo donde se activa el mecanismo para engrapar
#define TIM_SIG_ENGRAPAR 1000//Tiempo que permanece la segnal de engrapado en el rele


#define TIM_ENTRADA_TOPE_ENGRAPAR 100//Tiempo donde se activa el tope para el engrape del papel, puede ser el mismo que TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL
#define TIM_SIG_TOPE_ENGRAPAR 4000//Tiempo que permanece la segnal del tope engrapado en el rele


#define TIM_ENTRADA_AVANCE_PAPEL_ENGRAPADORA 1200//Tiempo donde se activa el mecanismo avanzar el papel despues de ser engrapado
#define TIM_SIG_AVANCE_PAPEL_ENGRAPADORA 500//Tiempo que permanece la segnal de avance del papel hacia la dobladora

//Dobladora
#define TIM_ENTRADA_TOPE_DOBLADORA 1500//Tiempo donde se activa el tope para DOBLAR el papel
#define TIM_SIG_TOPE_DOBLADORA 500//Tiempo que permanece la segnal del tope DOBLADORA en el rele


#define TIM_ENTRADA_DOBLADORA 1300//Tiempo donde se activa la dobladora
#define TIM_SIG_DOBLADORA 500//Tiempo que permanece la segnal de la dobladora en el rele

#define  TIM_ENTRADA_BANDAS_DOBLADORA 1000 //Tiempo donde se activan las bandas de la dobladora

#define TIM_ENTRADA_SALIDA_CORRIENTE_DOBLADORA 1400//Tiempo donde se activa la salida de corriente para la salida del papel o la cortadora
#define TIM_SIG_SALIDA_CORRIENTE_DOBLADORA  500//Tiempo que permanece la segnal de la salida de corriente en el rele

//TORRE

#define TIM_FRECUENCIA_REVISAR_ENTRADA_PAPEL_TORRE 400//Tiempo de la frecuencia para revisar la entrada de papel


#endif
