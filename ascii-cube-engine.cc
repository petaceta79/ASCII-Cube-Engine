#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;


const float densidad = 0.3; // Cómo de relleno están los cubos

const int screen_width = 120; // Tamaño de la pantalla
const int screen_height = 60; 

const int K1 = 40;  // Factor de escala (más grande → más ancho)
const int K2 = 40;   // Factor distancia desde el 'ojo' (más grande → más pequeño y alejado)

const int pos_extra_x = 50; // Distancia que se suma a las x finales
const int pos_extra_y = 45; // Distancia que se suma a las y finales

// Textura de la cara de Creeper
const vector<vector<bool>> cara_creeper = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},    
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0}
};

// Funciones para dibujar las caras del cubo
void render_cara(const float &sinA, const float &cosA, const float &sinB, const float &cosB, const float &sinC, const float &cosC, vector<vector<string>> &output, vector<vector<float>> &zbuffer, const int pos, const int ancho, const int alto, int x_mov, int y_mov, int z_mov) {
    for (float i = -ancho/2; i <= ancho/2; i += densidad) {
        for (float e = -alto/2; e <= alto/2; e += densidad) {
            int cara = 0;
            float L = cosA*cosB;
            cara = (int) (L * 11);

            if (L < 0) {
                continue; 
            }

            float i_ = x_mov + i;
            float e_ = y_mov + e;
            float pos_ = z_mov + pos;

            float x = (i_*cosA + pos_*sinA)*cosC + (e_*cosB + (i_*sinA - pos_*cosA)*sinB)*sinC;
            float y = (e_*cosB + (i_*sinA - pos_*cosA)*sinB)*cosC - (i_*cosA + pos_*sinA)*sinC;
            float z = (i_*sinA - pos_*cosA)*cosB - e_*sinB;
            
            float ooz = 1/(z + K2);
            int xp = (int)(K1 * ooz * x + pos_extra_x);
            int yp = (int)(K1 * ooz * y + pos_extra_y);

            if (xp >= 0 && xp < screen_width && yp >= 0 && yp < screen_height) {
                if (ooz > zbuffer[yp][xp]) {
                    zbuffer[yp][xp] = ooz;

                    output[yp][xp] = ".,-~:;=!*#$@"[cara];
                    if (cara_creeper[(int)(e + alto/2)][(int)(i + ancho/2)]) {
                        output[yp][xp] = "\033[90m" + output[yp][xp] + "\033[0m";
                    }
                    else {
                        output[yp][xp] = "\033[32m" + output[yp][xp] + "\033[0m";
                    }
                }
            }

        }
    }
}

void render_pared_delantera(const float &sinA, const float &cosA, const float &sinB, const float &cosB, const float &sinC, const float &cosC, vector<vector<string>> &output, vector<vector<float>> &zbuffer, const int pos, const int ancho, const int alto, int x_mov, int y_mov, int z_mov, string ansi_code) {
    for (float i = -ancho/2; i <= ancho/2; i += densidad) {
        for (float e = -alto/2; e <= alto/2; e += densidad) {
            int cara = 0;
            float L = cosA*cosB;
            cara = (int) (L * 11);

            if (L < 0) {
                continue; 
            }

            float i_ = x_mov + i;
            float e_ = y_mov + e;
            float pos_ = z_mov + pos;

            float x = (i_*cosA + pos_*sinA)*cosC + (e_*cosB + (i_*sinA - pos_*cosA)*sinB)*sinC;
            float y = (e_*cosB + (i_*sinA - pos_*cosA)*sinB)*cosC - (i_*cosA + pos_*sinA)*sinC;
            float z = (i_*sinA - pos_*cosA)*cosB - e_*sinB;
            
            float ooz = 1/(z + K2);
            int xp = (int)(K1 * ooz * x + pos_extra_x);
            int yp = (int)(K1 * ooz * y + pos_extra_y);

            if (xp >= 0 && xp < screen_width && yp >= 0 && yp < screen_height) {
                if (ooz > zbuffer[yp][xp]) {
                    zbuffer[yp][xp] = ooz;

                    output[yp][xp] = ".,-~:;=!*#$@"[cara];
                    output[yp][xp] = "\033[" + ansi_code + "m" + output[yp][xp] + "\033[0m";
                }
            }

        }
    }
}

void render_pared_trasera(const float &sinA, const float &cosA, const float &sinB, const float &cosB, const float &sinC, const float &cosC, vector<vector<string>> &output, vector<vector<float>> &zbuffer, int pos, const int ancho, const int alto, int x_mov, int y_mov, int z_mov, string ansi_code) {
    for (float i = -ancho/2; i <= ancho/2; i += densidad) {
        for (float e = -alto/2; e <= alto/2; e += densidad) {
            int cara = 0;
            float L = -cosA*cosB;
            cara = (int) (L * 11);

            if (L < 0) {
                continue; 
            }

            float i_ = x_mov + i;
            float e_ = y_mov + e;
            float pos_ = z_mov + pos;

            float x = (i_*cosA + pos_*sinA)*cosC + (e_*cosB + (i_*sinA - pos_*cosA)*sinB)*sinC;
            float y = (e_*cosB + (i_*sinA - pos_*cosA)*sinB)*cosC - (i_*cosA + pos_*sinA)*sinC;
            float z = (i_*sinA - pos_*cosA)*cosB - e_*sinB;
            
            float ooz = 1/(z + K2);
            int xp = (int)(K1 * ooz * x + pos_extra_x);
            int yp = (int)(K1 * ooz * y + pos_extra_y);

            if (xp >= 0 && xp < screen_width && yp >= 0 && yp < screen_height) {
                if (ooz > zbuffer[yp][xp]) {
                    zbuffer[yp][xp] = ooz;

                    output[yp][xp] = ".,-~:;=!*#$@"[cara];
                    output[yp][xp] = "\033[" + ansi_code + "m" + output[yp][xp] + "\033[0m";
                }
            }

        }
    }
}

void render_pared_dere(const float &sinA, const float &cosA, const float &sinB, const float &cosB, const float &sinC, const float &cosC, vector<vector<string>> &output, vector<vector<float>> &zbuffer, const int pos, const int ancho, const int alto, int x_mov, int y_mov, int z_mov, string ansi_code) {
    for (float i = -ancho/2; i <= ancho/2; i += densidad) {
        for (float e = -alto/2; e <= alto/2; e += densidad) {
            int cara = 0;
            float L = -sinA*cosB;
            cara = (int) (L * 11);

            if (L < 0) {
                continue; 
            }

            float i_ = x_mov + i;
            float e_ = y_mov + e;
            float pos_ = z_mov + pos;

            float x = (pos_*cosA - e_*sinA)*cosC + (i_*cosB + (pos_*sinA + e_*cosA)*sinB)*sinC;
            float y = (i_*cosB + (pos_*sinA + e_*cosA)*sinB)*cosC - (pos_*cosA - e_*sinA)*sinC;
            float z = (pos_*sinA + e_*cosA)*cosB - i_*sinB;
            
            float ooz = 1/(z + K2);
            int xp = (int)(K1 * ooz * x + pos_extra_x);
            int yp = (int)(K1 * ooz * y + pos_extra_y);

            if (xp >= 0 && xp < screen_width && yp >= 0 && yp < screen_height) {
                if (ooz > zbuffer[yp][xp]) {
                    zbuffer[yp][xp] = ooz;

                    output[yp][xp] = ".,-~:;=!*#$@"[cara];
                    output[yp][xp] = "\033[" + ansi_code + "m" + output[yp][xp] + "\033[0m";
                }
            }

        }
    }
}

void render_pared_izq(const float &sinA, const float &cosA, const float &sinB, const float &cosB, const float &sinC, const float &cosC, vector<vector<string>> &output, vector<vector<float>> &zbuffer, const int pos, const int ancho, const int alto, int x_mov, int y_mov, int z_mov, string ansi_code) {
    for (float i = -ancho/2; i <= ancho/2; i += densidad) {
        for (float e = -alto/2; e <= alto/2; e += densidad) {
            int cara = 0;
            float L = sinA*cosB;
            cara = (int) (L * 11);

            if (L < 0) {
                continue; 
            }

            float i_ = x_mov + i;
            float e_ = y_mov + e;
            float pos_ = z_mov + pos;

            float x = (pos_*cosA - e_*sinA)*cosC + (i_*cosB + (pos_*sinA + e_*cosA)*sinB)*sinC;
            float y = (i_*cosB + (pos_*sinA + e_*cosA)*sinB)*cosC - (pos_*cosA - e_*sinA)*sinC;
            float z = (pos_*sinA + e_*cosA)*cosB - i_*sinB;
            
            float ooz = 1/(z + K2);
            int xp = (int)(K1 * ooz * x + pos_extra_x);
            int yp = (int)(K1 * ooz * y + pos_extra_y);

            if (xp >= 0 && xp < screen_width && yp >= 0 && yp < screen_height) {
                if (ooz > zbuffer[yp][xp]) {
                    zbuffer[yp][xp] = ooz;

                    output[yp][xp] = ".,-~:;=!*#$@"[cara];
                    output[yp][xp] = "\033[" + ansi_code + "m" + output[yp][xp] + "\033[0m";
                }
            }

        }
    }
}

void render_suelo(const float &sinA, const float &cosA, const float &sinB, const float &cosB, const float &sinC, const float &cosC, vector<vector<string>> &output, vector<vector<float>> &zbuffer, const int pos, const int ancho, const int alto, int x_mov, int y_mov, int z_mov, string ansi_code) {
    for (float i = -ancho/2; i <= ancho/2; i += densidad) {
        for (float e = -alto/2; e <= alto/2; e += densidad) {
            int cara = 0;
            float L = sinB;
            cara = (int) (L * 11);

            if (L < 0) {
                continue; 
            }

            float i_ = x_mov + i;
            float e_ = y_mov + e;
            float pos_ = z_mov + pos;

            float x = (i_*cosA - e_*sinA)*cosC + (pos_*cosB + (i_*sinA + e_*cosA)*sinB)*sinC;
            float y = (pos_*cosB + (i_*sinA + e_*cosA)*sinB)*cosC - (i_*cosA - e_*sinA)*sinC;
            float z = (i_*sinA + e_*cosA)*cosB - pos_*sinB;
            
            float ooz = 1/(z + K2);
            int xp = (int)(K1 * ooz * x + pos_extra_x);
            int yp = (int)(K1 * ooz * y + pos_extra_y);

            if (xp >= 0 && xp < screen_width && yp >= 0 && yp < screen_height) {
                if (ooz > zbuffer[yp][xp]) {
                    zbuffer[yp][xp] = ooz;

                    output[yp][xp] = ".,-~:;=!*#$@"[cara];
                    output[yp][xp] = "\033[" + ansi_code + "m" + output[yp][xp] + "\033[0m";
                }
            }

        }
    }
}

void render_techo(const float &sinA, const float &cosA, const float &sinB, const float &cosB, const float &sinC, const float &cosC, vector<vector<string>> &output, vector<vector<float>> &zbuffer, const int pos, const int ancho, const int alto, int x_mov, int y_mov, int z_mov, string ansi_code) {
    for (float i = -ancho/2; i <= ancho/2; i += densidad) {
        for (float e = -alto/2; e <= alto/2; e += densidad) {
            int cara = 0;
            float L = -sinB;
            cara = (int) (L * 11);

            if (L < 0) {
                continue; 
            }

            float i_ = x_mov + i;
            float e_ = y_mov + e;
            float pos_ = z_mov + pos;

            float x = (i_*cosA - e_*sinA)*cosC + (pos_*cosB + (i_*sinA + e_*cosA)*sinB)*sinC;
            float y = (pos_*cosB + (i_*sinA + e_*cosA)*sinB)*cosC - (i_*cosA - e_*sinA)*sinC;
            float z = (i_*sinA + e_*cosA)*cosB - pos_*sinB;
            
            float ooz = 1/(z + K2);
            int xp = (int)(K1 * ooz * x + pos_extra_x);
            int yp = (int)(K1 * ooz * y + pos_extra_y);

            if (xp >= 0 && xp < screen_width && yp >= 0 && yp < screen_height) {
                if (ooz > zbuffer[yp][xp]) {
                    zbuffer[yp][xp] = ooz;

                    output[yp][xp] = ".,-~:;=!*#$@"[cara];
                    output[yp][xp] = "\033[" + ansi_code + "m" + output[yp][xp] + "\033[0m";
                }
            }

        }
    }
}

// Funciones para el renderizado de cubos u objetos
/*
  ancho = anchura del cubo
  alto = altura del cubo
  profundo = profundidad del cubo
  x = posición x en el espacio 3D del cubo
  y = posición y en el espacio 3D del cubo
  z = posición z en el espacio 3D del cubo
  (sinA, cosA, sinB, cosB, sinC, cosC) = valores precalculados para optimizar el tiempo de ejecución
  output = estructura interna donde se guardarán los píxeles correspondientes
  zbuffer = estructura interna donde se guardará la profundidad de cada píxel del output
  ansi_codes = vector que asigna a cada cara el valor ANSI indicado con el orden (delante, derecha, detrás, izquierda, abajo, arriba)
*/
void render_cubo(const int ancho, const int alto, const int profundo, const int x, const int y, const int z, const float &sinA, const float &cosA, const float &sinB, const float &cosB, const float &sinC, const float &cosC, vector<vector<string>> &output, vector<vector<float>> &zbuffer, vector<string> ansi_codes) {
    // pared trasera 
    render_pared_trasera(sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, -(profundo/2), ancho, alto, x, y, -z, ansi_codes[2]);
    
    // pared delantera
    render_pared_delantera(sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, (profundo/2), ancho, alto, x, y, -z, ansi_codes[0]);

    // pared dere
    render_pared_dere(sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, (ancho/2), alto, profundo, y, z, x, ansi_codes[1]);

    // pared izq
    render_pared_izq(sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, -(ancho/2), alto, profundo, y, z, x, ansi_codes[3]);

    // suelo
    render_suelo(sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, (alto/2), ancho, profundo, x, z, y, ansi_codes[4]);

    // techo
    render_techo(sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, -(alto/2), ancho, profundo, x, z, y, ansi_codes[5]);
    
}

void render_cabeza_creeper(const int ancho, const int alto, const int profundo, const int x, const int y, const int z, const float &sinA, const float &cosA, const float &sinB, const float &cosB, const float &sinC, const float &cosC, vector<vector<string>> &output, vector<vector<float>> &zbuffer) {
    // pared trasera 
    render_pared_trasera(sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, -(profundo/2), ancho, alto, x, y, -z, "32");
    
    // pared delantera
    render_cara(sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, (profundo/2), ancho, alto, x, y, -z);

    // pared dere
    render_pared_dere(sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, (ancho/2), alto, profundo, y, z, x, "32");

    // pared izq
    render_pared_izq(sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, -(ancho/2), alto, profundo, y, z, x, "32");

    // techo
    render_techo(sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, (alto/2), ancho, profundo, x, z, y, "32");

    // suelo
    render_suelo(sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, -(alto/2), ancho, profundo, x, z, y, "32");
    
}

void render_creeper(const float &sinA, const float &cosA, const float &sinB, const float &cosB, const float &sinC, const float &cosC, vector<vector<string>> &output, vector<vector<float>> &zbuffer, const int x, const int y, const int z) {
    render_cabeza_creeper(8, 8, 8, 0 + x, 0 + y, 0 + z, sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer);

    render_cubo(4, 8, 4, 0 + x, 8 + y, 0 + z, sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, vector<string>(6,"32"));

    render_cubo(6, 2, 2, 0 + x, 14 + y, 2 + z, sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, vector<string>(6,"32"));

    render_cubo(6, 2, 2, 0 + x, 14 + y, -2 + z, sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, vector<string>(6,"32"));
}

// Función que se ejecuta cada frame, para renderizar la pantalla en sí
void render_frame(float A, float B, float C) {

    // Cálculos previos
    vector<vector<string>> output(screen_height, vector<string>(screen_width, " "));
    vector<vector<float>> zbuffer(screen_height, vector<float>(screen_width, 0));

    const float sinA = sin(A), cosA = cos(A);
    const float sinB = sin(B), cosB = cos(B);
    const float sinC = sin(C), cosC = cos(C);    


    // Objetos a renderizar
    render_cubo(6, 6, 6, 0, 0, 0, sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, {"37", "37", "37", "37", "37", "37"});
    render_cubo(6, 6, 6, 6, 0, 0, sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, {"33", "33", "33", "33", "33", "33"});
    render_cubo(6, 6, 6, -6, 0, 0, sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, {"31", "31", "31", "31", "31", "31"});
    render_cubo(6, 6, 6, 0, 0, 6, sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, {"38;5;208", "38;5;208", "38;5;208", "38;5;208", "38;5;208", "38;5;208"});
    render_cubo(6, 6, 6, 6, 0, 6, sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, {"34", "34", "34", "34", "34", "34"});
    render_cubo(6, 6, 6, -6, 0, 6, sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, {"32", "32", "32", "32", "32", "32"});
    render_cubo(6, 6, 6, -6, 0, 6, sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, {"32", "32", "32", "32", "32", "32"});
    render_cubo(6, 6, 6, 0, 0, -6, sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, {"38;5;201", "38;5;201", "38;5;201", "38;5;201", "38;5;201", "38;5;201"});
    render_cubo(6, 6, 6, -6, 0, -6, sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, {"38;5;93", "38;5;93", "38;5;93", "38;5;93", "38;5;93", "38;5;93"});
    render_cubo(6, 6, 6, 6, 0, -6, sinA, cosA, sinB, cosB, sinC, cosC, output, zbuffer, {"38;5;51", "38;5;51", "38;5;51", "38;5;51", "38;5;51", "38;5;51"});


    // Impresión del buffer de salida 
    string buffer;
    buffer.reserve(screen_width * screen_height + screen_height); 

    for (int j = 0; j < screen_height; j++) {
        for (int i = 0; i < screen_width; i++) {
            buffer += (output[j][i]);
        }
        buffer.push_back('\n');
    }

    cout << buffer;
}

int main() {
    float A = 0; // Inicio del ángulo de rotación en el eje y
    float B = 0; // Inicio del ángulo de rotación en el eje x
    float C = 0; // Inicio del ángulo de rotación en el eje z
    int retraso_ms = 20; // Retraso en milisegundos por cada frame

    while (true) {
        cout << "\033[H"; 

        // Renderizar lo programado
        render_frame(A, B, C);

        // Sumar a la rotación actual (para hacer que gire)
        A += 0.04;
        B += 0.04;
        C += 0.04;

        // Delay entre frames
        clock_t start_time = clock();
        while (clock() < start_time + retraso_ms * CLOCKS_PER_SEC / 1000);
    }

    return 0;
}