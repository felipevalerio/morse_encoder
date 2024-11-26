#include <Arduino.h>
#include <string.h>
#include <ctype.h>

int buzzer = 8; // pino digital 8, onde o buzzer está conectado
bool played = false; // para tocar apenas 
const char *text = "SOS"; // texto que será codificado


typedef struct {

  const char *letter;
  const char *code;

} MorseCode;


MorseCode morse_code[] = {
    {"A", ".-"}, {"B", "-..."}, {"C", "-.-."}, {"D", "-.."},
    {"E", "."}, {"F", "..-."}, {"G", "--."}, {"H", "...."},
    {"I", ".."}, {"J", ".---"}, {"K", "-.-"}, {"L", ".-.."},
    {"M", "--"}, {"N", "-."}, {"O", "---"}, {"P", ".--."},
    {"Q", "--.-"}, {"R", ".-."}, {"S", "..."}, {"T", "-"},
    {"U", "..-"}, {"V", "...-"}, {"W", ".--"}, {"X", "-..-"},
    {"Y", "-.--"}, {"Z", "--.."}, {"1", ".----"}, {"2", "..---"},
    {"3", "...--"}, {"4", "....-"}, {"5", "....."}, {"6", "-...."},
    {"7", "--..."}, {"8", "---.."}, {"9", "----."}, {"0", "-----"},
    {NULL, NULL}
};


// função para percorrer o alfabeto e retornar sua representação em código Morse
const char *get_morse_code(const char *letter) {
  
  for (int i = 0; i < morse_code[i].letter != NULL; i++) { // percorre o vetor de instâncias até encontrar NULL
    if(strcmp(morse_code[i].letter, letter) == 0) { // se encontrar, compara as letras. A == A
      return morse_code[i].code; // retorna o código. Por exemplo A => .-
    }
  }
      
  return NULL;
}

// função que irá receber os códigos morses, reconhecer e tocar de acordo com os tempos determinados
void play_beeps(const char *code) {

  while (*code) {

    if (*code == '.') { // Ponto curto

      tone(buzzer, 4400);
      delay(150);
    } else if (*code == '-') { // Traço longo

      tone(buzzer, 4400);
      delay(550);
    }

    noTone(buzzer);
    delay(150);  // Espaço entre pontos/traços
    code++;

    // switch(*code) {

    //   case '.':

    //     tone(buzzer, 4400);
    //     delay(150);
    //   case '-':
    //     tone(buzzer, 4400);
    //     delay(550);
    // }
  }
  delay(1000);  // Espaço entre letras
}


void setup() {
	pinMode(buzzer, OUTPUT); //Definindo o pino buzzer como de saída.
}

void loop() {
  if (!played) {
    char letter[2] = {0}; // letra + o terminador nulo (\0) Por exemplo: 'S' '\0'

    for (int i = 0; i < strlen(text); i++) {

      letter[0] = toupper(text[i]); // letras maiusculas
      const char *code = get_morse_code(letter);
      if (code != NULL) {
        play_beeps(code);
      }
    }

    played = true;
  }
}