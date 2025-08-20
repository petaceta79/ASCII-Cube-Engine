#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;


const float densidad = 0.3; // Cómo de relleno están los cubos

const int screen_width = 120;   
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
void render_cara(const float &sinA, const float &cosA, const float &sinB, const float &cosB, vector<vector<string>> &output, vector<vector<float>> &zbuffer, const int pos, const int ancho, const int alto, int x_mov, int y_mov, int z_mov) {
    for (float i = -ancho/2; i <= ancho/2; i += densidad) {
        for (float e = -alto/2; e <= alto/2; e += densidad) {
            int cara = 0;
            float L = cosA*cosB;
            cara = (int) (L * 11);

            if (L <= 0) {
                continue; 
            }

            float i_ = x_mov + i;
            float e_ = y_mov + e;
            float pos_ = z_mov + pos;

            float x = i_*cosA + pos_*sinA;
            float y = e_*cosB + (i_*sinA - pos_*cosA)*sinB;
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

void render_pared_delantera(const float &sinA, const float &cosA, const float &sinB, const float &cosB, vector<vector<string>> &output, vector<vector<float>> &zbuffer, const int pos, const int ancho, const int alto, int x_mov, int y_mov, int z_mov) {
    for (float i = -ancho/2; i <= ancho/2; i += densidad) {
        for (float e = -alto/2; e <= alto/2; e += densidad) {
            int cara = 0;
            float L = cosA*cosB;
            cara = (int) (L * 11);

            if (L <= 0) {
                continue; 
            }

            float i_ = x_mov + i;
            float e_ = y_mov + e;
            float pos_ = z_mov + pos;

            float x = i_*cosA + pos_*sinA;
            float y = e_*cosB + (i_*sinA - pos_*cosA)*sinB;
            float z = (i_*sinA - pos_*cosA)*cosB - e_*sinB;
            
            float ooz = 1/(z + K2);
            int xp = (int)(K1 * ooz * x + pos_extra_x);
            int yp = (int)(K1 * ooz * y + pos_extra_y);

            if (xp >= 0 && xp < screen_width && yp >= 0 && yp < screen_height) {
                if (ooz > zbuffer[yp][xp]) {
                    zbuffer[yp][xp] = ooz;

                    output[yp][xp] = ".,-~:;=!*#$@"[cara];
                    output[yp][xp] = "\033[32m" + output[yp][xp] + "\033[0m";
                }
            }

        }
    }
}

void render_pared_trasera(const float &sinA, const float &cosA, const float &sinB, const float &cosB, vector<vector<string>> &output, vector<vector<float>> &zbuffer, int pos, const int ancho, const int alto, int x_mov, int y_mov, int z_mov) {
    for (float i = -ancho/2; i <= ancho/2; i += densidad) {
        for (float e = -alto/2; e <= alto/2; e += densidad) {
            int cara = 0;
            float L = -cosA*cosB;
            cara = (int) (L * 11);

            if (L <= 0) {
                continue; 
            }

            float i_ = x_mov + i;
            float e_ = y_mov + e;
            float pos_ = z_mov + pos;


            float x = i_*cosA + pos_*sinA;
            float y = e_*cosB + (i_*sinA - pos_*cosA)*sinB;
            float z = (i_*sinA - pos_*cosA)*cosB - e_*sinB;
            
            float ooz = 1/(z + K2);
            int xp = (int)(K1 * ooz * x + pos_extra_x);
            int yp = (int)(K1 * ooz * y + pos_extra_y);

            if (xp >= 0 && xp < screen_width && yp >= 0 && yp < screen_height) {
                if (ooz > zbuffer[yp][xp]) {
                    zbuffer[yp][xp] = ooz;

                    output[yp][xp] = ".,-~:;=!*#$@"[cara];
                    output[yp][xp] = "\033[32m" + output[yp][xp] + "\033[0m";
                }
            }

        }
    }
}

void render_pared_dere(const float &sinA, const float &cosA, const float &sinB, const float &cosB, vector<vector<string>> &output, vector<vector<float>> &zbuffer, const int pos, const int ancho, const int alto, int x_mov, int y_mov, int z_mov) {
    for (float i = -ancho/2; i <= ancho/2; i += densidad) {
        for (float e = -alto/2; e <= alto/2; e += densidad) {
            int cara = 0;
            float L = -sinA*cosB;
            cara = (int) (L * 11);

            if (L <= 0) {
                continue; 
            }

            float i_ = x_mov + i;
            float e_ = y_mov + e;
            float pos_ = z_mov + pos;

            float x = pos_*cosA - e_*sinA;
            float y = i_*cosB + (pos_*sinA + e_*cosA)*sinB;
            float z = (pos_*sinA + e_*cosA)*cosB - i_*sinB;
            
            float ooz = 1/(z + K2);
            int xp = (int)(K1 * ooz * x + pos_extra_x);
            int yp = (int)(K1 * ooz * y + pos_extra_y);

            if (xp >= 0 && xp < screen_width && yp >= 0 && yp < screen_height) {
                if (ooz > zbuffer[yp][xp]) {
                    zbuffer[yp][xp] = ooz;

                    output[yp][xp] = ".,-~:;=!*#$@"[cara];
                    output[yp][xp] = "\033[32m" + output[yp][xp] + "\033[0m";
                }
            }

        }
    }
}

void render_pared_izq(const float &sinA, const float &cosA, const float &sinB, const float &cosB, vector<vector<string>> &output, vector<vector<float>> &zbuffer, const int pos, const int ancho, const int alto, int x_mov, int y_mov, int z_mov) {
    for (float i = -ancho/2; i <= ancho/2; i += densidad) {
        for (float e = -alto/2; e <= alto/2; e += densidad) {
            int cara = 0;
            float L = sinA*cosB;
            cara = (int) (L * 11);

            if (L <= 0) {
                continue; 
            }

            float i_ = x_mov + i;
            float e_ = y_mov + e;
            float pos_ = z_mov + pos;

            float x = pos_*cosA - e_*sinA;
            float y = i_*cosB + (pos_*sinA + e_*cosA)*sinB;
            float z = (pos_*sinA + e_*cosA)*cosB - i_*sinB;
            
            float ooz = 1/(z + K2);
            int xp = (int)(K1 * ooz * x + pos_extra_x);
            int yp = (int)(K1 * ooz * y + pos_extra_y);

            if (xp >= 0 && xp < screen_width && yp >= 0 && yp < screen_height) {
                if (ooz > zbuffer[yp][xp]) {
                    zbuffer[yp][xp] = ooz;

                    output[yp][xp] = ".,-~:;=!*#$@"[cara];
                    output[yp][xp] = "\033[32m" + output[yp][xp] + "\033[0m";
                }
            }

        }
    }
}

void render_techo(const float &sinA, const float &cosA, const float &sinB, const float &cosB, vector<vector<string>> &output, vector<vector<float>> &zbuffer, const int pos, const int ancho, const int alto, int x_mov, int y_mov, int z_mov) {
    for (float i = -ancho/2; i <= ancho/2; i += densidad) {
        for (float e = -alto/2; e <= alto/2; e += densidad) {
            int cara = 0;
            float L = sinB;
            cara = (int) (L * 11);

            if (L <= 0) {
                continue; 
            }

            float i_ = x_mov + i;
            float e_ = y_mov + e;
            float pos_ = z_mov + pos;

            float x = i_*cosA - e_*sinA;
            float y = pos_*cosB + (i_*sinA + e_*cosA)*sinB;
            float z = (i_*sinA + e_*cosA)*cosB - pos_*sinB;
            
            float ooz = 1/(z + K2);
            int xp = (int)(K1 * ooz * x + pos_extra_x);
            int yp = (int)(K1 * ooz * y + pos_extra_y);

            if (xp >= 0 && xp < screen_width && yp >= 0 && yp < screen_height) {
                if (ooz > zbuffer[yp][xp]) {
                    zbuffer[yp][xp] = ooz;

                    output[yp][xp] = ".,-~:;=!*#$@"[cara];
                    output[yp][xp] = "\033[32m" + output[yp][xp] + "\033[0m";
                }
            }

        }
    }
}

void render_suelo(const float &sinA, const float &cosA, const float &sinB, const float &cosB, vector<vector<string>> &output, vector<vector<float>> &zbuffer, const int pos, const int ancho, const int alto, int x_mov, int y_mov, int z_mov) {
    for (float i = -ancho/2; i <= ancho/2; i += densidad) {
        for (float e = -alto/2; e <= alto/2; e += densidad) {
            int cara = 0;
            float L = -sinB;
            cara = (int) (L * 11);

            if (L <= 0) {
                continue; 
            }

            float i_ = x_mov + i;
            float e_ = y_mov + e;
            float pos_ = z_mov + pos;

            float x = i_*cosA - e_*sinA;
            float y = pos_*cosB + (i_*sinA + e_*cosA)*sinB;
            float z = (i_*sinA + e_*cosA)*cosB - pos_*sinB;
            
            float ooz = 1/(z + K2);
            int xp = (int)(K1 * ooz * x + pos_extra_x);
            int yp = (int)(K1 * ooz * y + pos_extra_y);

            if (xp >= 0 && xp < screen_width && yp >= 0 && yp < screen_height) {
                if (ooz > zbuffer[yp][xp]) {
                    zbuffer[yp][xp] = ooz;

                    output[yp][xp] = ".,-~:;=!*#$@"[cara];
                    output[yp][xp] = "\033[32m" + output[yp][xp] + "\033[0m";
                }
            }

        }
    }
}

// Funciones para el renderizado de cubos u objetos
void render_cubo(const int ancho, const int alto, const int profundo, const int x, const int y, const int z, const float &sinA, const float &cosA, const float &sinB, const float &cosB, vector<vector<string>> &output, vector<vector<float>> &zbuffer) {
    // pared trasera 
    render_pared_trasera(sinA, cosA, sinB, cosB, output, zbuffer, -(profundo/2), ancho, alto, x, y, -z);
    
    // pared delantera
    render_pared_delantera(sinA, cosA, sinB, cosB, output, zbuffer, (profundo/2), ancho, alto, x, y, -z);

    // pared dere
    render_pared_dere(sinA, cosA, sinB, cosB, output, zbuffer, (ancho/2), alto, profundo, y, z, x);

    // pared izq
    render_pared_izq(sinA, cosA, sinB, cosB, output, zbuffer, -(ancho/2), alto, profundo, y, z, x);

    // techo
    render_techo(sinA, cosA, sinB, cosB, output, zbuffer, (alto/2), ancho, profundo, x, z, y);

    // suelo
    render_suelo(sinA, cosA, sinB, cosB, output, zbuffer, -(alto/2), ancho, profundo, x, z, y);
    
}

void render_cabeza_creeper(const int ancho, const int alto, const int profundo, const int x, const int y, const int z, const float &sinA, const float &cosA, const float &sinB, const float &cosB, vector<vector<string>> &output, vector<vector<float>> &zbuffer) {
    // pared trasera 
    render_pared_trasera(sinA, cosA, sinB, cosB, output, zbuffer, -(profundo/2), ancho, alto, x, y, -z);
    
    // pared delantera
    render_cara(sinA, cosA, sinB, cosB, output, zbuffer, (profundo/2), ancho, alto, x, y, -z);

    // pared dere
    render_pared_dere(sinA, cosA, sinB, cosB, output, zbuffer, (ancho/2), alto, profundo, y, z, x);

    // pared izq
    render_pared_izq(sinA, cosA, sinB, cosB, output, zbuffer, -(ancho/2), alto, profundo, y, z, x);

    // techo
    render_techo(sinA, cosA, sinB, cosB, output, zbuffer, (alto/2), ancho, profundo, x, z, y);

    // suelo
    render_suelo(sinA, cosA, sinB, cosB, output, zbuffer, -(alto/2), ancho, profundo, x, z, y);
    
}

void render_creeper(const float &sinA, const float &cosA, const float &sinB, const float &cosB, vector<vector<string>> &output, vector<vector<float>> &zbuffer, const int x, const int y, const int z) {
    render_cabeza_creeper(8, 8, 8, 0 + x, 0 + y, 0 + z, sinA, cosA, sinB, cosB, output, zbuffer);

    render_cubo(4, 8, 4, 0 + x, 8 + y, 0 + z, sinA, cosA, sinB, cosB, output, zbuffer);

    render_cubo(6, 2, 2, 0 + x, 14 + y, 2 + z, sinA, cosA, sinB, cosB, output, zbuffer);

    render_cubo(6, 2, 2, 0 + x, 14 + y, -2 + z, sinA, cosA, sinB, cosB, output, zbuffer);
}

// Función que se ejecuta cada frame, para renderizar la pantalla en sí
void render_frame(float A, float B) {

    // Cálculos previos
    vector<vector<string>> output(screen_height, vector<string>(screen_width, " "));
    vector<vector<float>> zbuffer(screen_height, vector<float>(screen_width, 0));

    const float sinA = sin(A), cosA = cos(A);
    const float sinB = sin(B), cosB = cos(B);


    // Objetos a renderizar
    render_cubo(8, 8, 8, 0, -7, 0, sinA, cosA, sinB, cosB, output, zbuffer);
    render_cubo(8, 8, 8, 7, 7, 7, sinA, cosA, sinB, cosB, output, zbuffer);
    render_cubo(8, 8, 8, -7, 7, -7, sinA, cosA, sinB, cosB, output, zbuffer);


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
    int retraso_ms = 20; // Retraso en milisegundos por cada frame

    while (true) {
        cout << "\033[H"; 

        // Renderizar lo programado
        render_frame(A, B);

        // Sumar a la rotación actual (para hacer que gire)
        A += 0.05;
        B += 0.04;

        // Delay entre frames
        clock_t start_time = clock();
        while (clock() < start_time + retraso_ms * CLOCKS_PER_SEC / 1000);
    }

    return 0;
}