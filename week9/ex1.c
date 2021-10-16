#include <stdio.h>
#include <stdlib.h>


struct page_frame {
    int id;
    int rank;
};


int main(int argc, char* argv[]) {
    /* simulates a paging system using the ageing algorithm */
    int page_frames_number = 10;
    if(argc > 1) {
        page_frames_number = atoi(argv[1]);
    }

    struct page_frame * page_frames = calloc(page_frames_number, sizeof(struct page_frame));
    for(int i = 0; i < page_frames_number; i++) {
        page_frames[i].id = -1;
        page_frames[i].rank = 0;
    }

    printf("Print the number of pages");

    int hits = 0;
    int misses = 0;

    int page_id;
    FILE *file;
    file = fopen("ex1_input.txt", "r");
    for(int i = 0;; i++) {
        if(fscanf(file, "%d", &page_id) == EOF) {
            break;
        }

        int is_hit = 0;
        int min_rank_i = 0;
        int min_rank = -1;
        for(int i = 0; i < page_frames_number; i++) {
            printf("\ni = %d id = %d %d", i, page_frames[i].id, page_frames[i].rank);

            if(min_rank == -1 || min_rank > page_frames[i].rank) {
                min_rank = page_frames[i].rank;
                min_rank_i = i;
            }
            if(page_id == page_frames[i].id) {
                /* hit */
                page_frames[i].rank += 65536;
                hits += 1;
                is_hit = 1;
            }
            page_frames[i].rank >>= 1;
        }

        if(!is_hit) {
            /* miss */
            page_frames[min_rank_i].id = page_id;
            page_frames[min_rank_i].rank = 32768;
            misses += 1;
        }

        printf("\ncurrent page number %d\n", page_id);
    }

    printf("\nhit = %f miss = %f ratio = %f\n", (float) hits, (float) misses, (float) hits / (float) misses);

    free(page_frames);

    return 0;
}
