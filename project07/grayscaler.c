#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "ppm.h"

struct thread_data {
    struct ppm *img;
    int start_y;
    int height;
    int thread_id;
    int sum_r;
    int sum_g;
    int sum_b;
};

void *greyscale_slice(void *arg){
    struct thread_data *td = (struct thread_data *)arg;
    int end_y = td->start_y + td->height;

    td->sum_r = 0;
    td->sum_g = 0;
    td->sum_b = 0;

    printf("Thread %d: %d %d\n", td->thread_id, td->start_y, td->height);

    for (int y = td->start_y; y < end_y; y++){
        for (int x = 0; x < td->img->width; x++){

            int pixel = ppm_get_pixel(td->img, x, y);

            int r = PPM_PIXEL_R(pixel);
            int g = PPM_PIXEL_G(pixel);
            int b = PPM_PIXEL_B(pixel);

            td->sum_r += r;
            td->sum_g += g;
            td->sum_b += b;

            int gray = (299*r + 587*g + 114*b) / 1000;

            ppm_set_pixel(td->img, x, y, PPM_PIXEL(gray, gray, gray));
        }
    }
    

    return NULL;
}

int main(int argc, char *argv[]){

    if (argc > 4){
        fprintf(stderr, "Usage: %s <threads> <input.ppm> <output.ppm>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    struct ppm *img = ppm_read(argv[2]);

    int slice_height = img->height / num_threads;
    int remainder = img->height % num_threads;

    pthread_t threads[num_threads];

    struct thread_data tdata[num_threads];

    for (int i = 0; i < num_threads; i++){
        tdata[i].img = img;
        tdata[i].start_y = i * slice_height;
        tdata[i].height = slice_height;
        tdata[i].thread_id = i;

        if (i == num_threads -1){
            tdata[i].height += remainder;
        }

        pthread_create(&threads[i], NULL, greyscale_slice, &tdata[i]);
    }

    long total_r = 0;
    long total_b = 0;
    long total_g = 0;
    long total_pixels = (long)img->width * img->height;

    for (int i =0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
        total_r += tdata[i].sum_r;
        total_g += tdata[i].sum_g;
        total_b += tdata[i].sum_b;
    }

    printf("Average R: %ld\n", total_r / total_pixels);
    printf("Average G: %ld\n", total_g / total_pixels);
    printf("Average B: %ld\n", total_b / total_pixels);

    ppm_write(img, argv[3]);
    ppm_free(img);
}