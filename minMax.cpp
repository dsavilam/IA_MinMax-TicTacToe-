#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Declaramos las variables globales de jugador y el oponente
char jugador = 'x';
char oponente = 'o';

struct Move
{
    int fil;
    int col;
};

// Evaluamos si quedan movimientos por hacer
bool isMovesLeft(char board[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j]=='_')
                return true;
    return false;
}

// Función de evaluación sacada de: (https://www.geeksforgeeks.org/dsa/introduction-to-evaluation-function-of-minMax-algorithm-in-game-theory/ )
int evaluate(char evaluatedBoard[3][3])
{
    // Nota -- Si gana el jugador, devolvemos +7, si gana el oponente, devolvemos -7 -- 
    // Todo esto inspirado de la pagina del GeeksForGeeks (Buenisima la pagina)

    // Verificamosmos filas para ver si hay victoria de alguno de los dos
    for (int fil = 0; fil < 3; fil++)
    {
        if (evaluatedBoard[fil][0]==evaluatedBoard[fil][1] && evaluatedBoard[fil][1]==evaluatedBoard[fil][2])
        {
            if (evaluatedBoard[fil][0]==jugador)
                return +7;
            else if (evaluatedBoard[fil][0]==oponente)
                return -7;
        }
    }

    // Verificamosmos columnas
    for (int col = 0; col<3; col++)
    {
        if (evaluatedBoard[0][col]==evaluatedBoard[1][col] && evaluatedBoard[1][col]==evaluatedBoard[2][col])
        {
            if (evaluatedBoard[0][col]==jugador)
                return +7;

            else if (evaluatedBoard[0][col]==oponente)
                return -7;
        }
    }

    // Verificamosmos las diagonales
    if (evaluatedBoard[0][0]==evaluatedBoard[1][1] && evaluatedBoard[1][1]==evaluatedBoard[2][2])
    {
        if (evaluatedBoard[0][0]==jugador)
            return +7;
        else if (evaluatedBoard[0][0]==oponente)
            return -7;
    }
    if (evaluatedBoard[0][2]==evaluatedBoard[1][1] && evaluatedBoard[1][1]==evaluatedBoard[2][0])
    {
        if (evaluatedBoard[0][2]==jugador)
            return +7;
        else if (evaluatedBoard[0][2]==oponente)
            return -7;
    }

    // Si ninguno de los dos ha ganado, retornamos un 0
    return 0;
}

// Funcion minMax, considera todos los 14.000.605 futuros que vio el Dr. Strange y retorna el valor del tablero
int minMax(char board[3][3], int depth, bool isMax)
{
    int score = evaluate(board);

    // Si el jugador (El maximizador) ha ganado el juego retorna su puntuación evaluada
    if (score == 7)
        return score;

    // Si el oponente/el impostor (Bueno, el minimizador) ha ganado el juego retorna su puntuación evaluada
    if (score == -7)
        return score;

    // Si no hay más movimientos y no hay ganador entonces empataron
    if (isMovesLeft(board)==false)
        return 0;

    // Si es el turno del maximizador
    if (isMax)
    {
        int best = -9999;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Verificamos si la celda está vacía
                if (board[i][j]=='_')
                {
                    // Realiza el movimiento
                    board[i][j] = jugador;

                    // Llama recursivamente a minMax y elige el valor máximo
                    best = max( best, minMax(board, depth+1, !isMax) );

                    // Deshace el movimiento
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }

    // Si es el turno del minimizador
    else
    {
        int best = 9999;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Verificamos si la celda está vacía
                if (board[i][j]=='_')
                {
                    // Realiza el movimiento
                    board[i][j] = oponente;

                    // Llama recursivamente a minMax y elige el valor mínimo
                    best = min(best, minMax(board, depth+1, !isMax));

                    // Deshace el movimiento
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

// Esto retornará el mejor movimiento posible para el jugador, sacado de: (https://www.geeksforgeeks.org/dsa/finding-optimal-move-in-tic-tac-toe-using-minMax-algorithm-in-game-theory/) 
Move findBestMove(char board[3][3])
{
    int bestVal = -9999;

    //Inicializamos con valores negativos
    Move bestMove;
    bestMove.fil = -1;
    bestMove.col = -1;

    // Recorre todas las celdas, evalúa la función minMax para todas las celdas vacías. Y retorna la celda con el valor óptimo.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Verificamos si la celda está vacía
            if (board[i][j]=='_')
            {
                // Realiza el movimiento
                board[i][j] = jugador;

                // Calcula la función de evaluación para este movimiento.
                int moveVal = minMax(board, 0, false);

                // Deshace el movimiento
                board[i][j] = '_';

                // Si el valor del movimiento actual es mayor que el mejor valor, actualiza el mejor
                if (moveVal > bestVal)
                {
                    bestMove.fil = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    cout << "El valor del mejor movimiento es : " << bestVal << endl;

    return bestMove;
}


int main()
{
    char opcion;

    cout << "Ingresa una opción del menu! " << endl;
    cout << "1. Ingresa tu tablero " << endl;
    cout << "2. Usa el tablero de prueba " << endl;
    cin >> opcion;

    if (opcion == '1'){

        char board [3][3];
        cout << "Ingresa tu tablero de triqui: " << endl;
        cout << "Recuerda 'x' para movimiento jugador, 'o' para oponente y '_' para el vacio (Caps sensitive jajdsaj)" << endl;

        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                cout << "Ingresa el movimiento de la fila " << i << " y columna " << j << ": ";
                cin >> board [i][j];
                if (board[i][j] != 'x' && board[i][j] != 'o' && board[i][j] != '_') {
                    cerr << "Tienes que ingresar uno de los caracteres permitidos, voy a estallar ahora! " << endl;
                    return -1;
                }
            }
        }


        cout << "Tu tablero quedo de la siguiente manera: " << endl;

          for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                cout << board [i][j];
            }
            cout << endl;
        }

        Move bestMove = findBestMove(board);

        cout << "El mejor movimiento posible es: " << endl;
        cout << "FILA: " << bestMove.fil << " COLUMNA: " <<  bestMove.col << endl;
    }
    
    if (opcion == '2'){

       char board[3][3] =
    {
        { 'x', 'x', 'o' },
        { 'o', 'x', 'o' },
        { '_', '_', '_' }
    };

    cout << "Para que lo recuerdes, el tablero que vamos a usar es: " << endl;

    for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                cout << board [i][j];
            }
            cout << endl;
        }


    Move bestMove = findBestMove(board);

    cout << "El mejor movimiento posible es: " << endl;
    cout << "FILA: " << bestMove.fil << " COLUMNA: " <<  bestMove.col << endl;
    }

    if (opcion != '1' && opcion != '2') {
        cout << "Ingresa una opción de verdad >:( " << endl;
    }
    
    return 0;
}