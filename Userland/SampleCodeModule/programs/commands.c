#include <commands.h>

#define YEAR 20			  // Debe escribir aca los digitos de su año (excepto los ultimos dos)
#define BYTES 32		  // Cantidad de bytes para el mem dump
#define FLOAT_PRECISION 8 // Precision para los puntos flotantes
//#define LAST_MEM_POSITION 536870911 //512MB mem que se le pasa en run.sh

// returns current date and time
void getCurrentDayTime(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 0)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	printf("\nFecha de hoy: ");
	uint64_t result = _syscall(SYS_RTC_ID, DAY_RTC_ID, 0, 0, 0, 0);
	printf("%d", result);
	putChar('/');

	result = _syscall(SYS_RTC_ID, MONTH_RTC_ID, 0, 0, 0, 0);
	printf("%d", result);
	putChar('/');

	result = _syscall(SYS_RTC_ID, YEAR_RTC_ID, 0, 0, 0, 0);
	printf("%d", YEAR);
	printf("%d\n", result);

	printf("\nHora: ");
	result = _syscall(SYS_RTC_ID, HOUR_RTC_ID, 0, 0, 0, 0);
	printf("%d", result);
	putChar(':');

	result = _syscall(SYS_RTC_ID, MINUTE_RTC_ID, 0, 0, 0, 0);
	if (result < 10)
	{
		putChar('0');
	}
	printf("%d", result);
	putChar(':');

	result = _syscall(SYS_RTC_ID, SECOND_RTC_ID, 0, 0, 0, 0);
	if (result < 10)
	{
		putChar('0');
	}
	printf("%d\n\n", result);
}

void getInfoReg(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 0)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	uint64_t *registers = (uint64_t *)_syscall(SYS_INFOREG_ID, 0, 0, 0, 0, 0);
	newLine();
	for (int i = 0; i < REGISTER_AMOUNT; i++)
	{
		printf("%s", registerNames[i]);
		printf("%x\n\n", registers[i]);
	}
	newLine();
}

void getMem(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 1)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	uint64_t memDir = strToHex(argv[0]);
	if (memDir == -1 /* || memDir + 32 > LAST_MEM_POSITION */)
	{
		printf("\nEl argumento ingresado es invalido. Use /help.\n\n");
		return;
	}

	printf("\nDump de 32 bytes a partir de la direccion: %s\n\n", argv[0]);
	uint8_t buffer[BYTES];
	char print[10];
	_syscall(SYS_PRINTMEM_ID, memDir, (uint64_t)buffer, BYTES, 0, 0);
	for (int i = 0; i < BYTES; i++)
	{
		if (i == 16)
		{
			newLine();
		}
		intToStr(buffer[i], print, 16);
		printf("%s ", print);
	}
	newLine();
	newLine();
}

void divZero(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 0)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	int x = 3;
	int y = 0;
	x = x / y;
}

// https://mudongliang.github.io/x86/html/file_module_x86_id_318.html
void opCode(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 0)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	_opcodeExp();
}

void clear(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 0)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	_syscall(SYS_CLEAR_ID, 0, 0, 0, 0, 0);
}
void exit(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 0)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	printf("\nSaliendo del TPE\n\n");
	_syscall(SYS_EXIT_ID, 0, 0, 0, 0, 0);
}

// void changeColour(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE], int ft)
// {
// 	if (argc != 1)
// 	{
// 		printf("\nCantidad invalida de argumentos.\n\n");
// 		return;
// 	}
// 	int aux = strToInt(argv[0], 0);
// 	if (ft == 1)
// 	{
// 		switch (aux)
// 		{
// 		case 1:
// 			setFTC(WHITE);
// 			break;
// 		case 2:
// 			setFTC(BLACK);
// 			break;
// 		case 3:
// 			setFTC(RED);
// 			break;
// 		case 4:
// 			setFTC(GREEN);
// 			break;
// 		case 5:
// 			setFTC(BLUE);
// 			break;
// 		default:
// 			printf("\nEl codigo de color que ingreso es invalido. Use /help.\n\n");
// 			break;
// 		}
// 	}
// 	else
// 	{
// 		switch (aux)
// 		{
// 		case 1:
// 			setBGC(WHITE);
// 			break;
// 		case 2:
// 			setBGC(BLACK);
// 			break;
// 		case 3:
// 			setBGC(RED);
// 			break;
// 		case 4:
// 			setBGC(GREEN);
// 			break;
// 		case 5:
// 			setBGC(BLUE);
// 			break;
// 		default:
// 			printf("\nEl codigo de color que ingreso es invalido. Use /help.\n\n");
// 			break;
// 		}
// 	}
// }

void help(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 0)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	printf("\nTabla de colores: \n");
	printf("\nBLANCO | NEGRO | ROJO | VERDE | AZUL\n");
	printf("  1    |   2   |  3   |   4   |  5\n");
	printf("\nLista de comandos: \n");
	printf("\nhelp : Listado de comandos\n");
	printf("\nclear : Limpia la pantalla actual\n");
	printf("\ninforeg : Estado de todos los resgitros.\n");
	printf("\ndate : Fecha y hora actual\n");
	printf("\nprintmem : Volcado de memoria de 32 bytes a partir de direccion de memoria en hexa ingresada como argumento.\n");
	// printf("La direccion debe estar comprendida en el rango: 0 - %x\n", LAST_MEM_POSITION - 32); CHEQUEO MAXMEM
	printf("\ndivzero : Excepcion division por cero\n");
	printf("\nopcode : Excepcion opcode invalido\n");
	// printf("\nftcolour : Cambia el color del texto. Pase el color como argumento usando la tabla de colores.\n\n");
	// printf("\nbgcolour : Cambia el color del fondo del texto. Pase el color como argumento usando la tabla de colores.\n\n");
	printf("\ngames : 4 ventanas que cuentan con los juegos sudoku y ahorcado, un cronometro y un timer\n");
	printf("\nexit : Finaliza la ejecucion.\n\n");
}

void games(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 0)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	while (startGames())
		;
}