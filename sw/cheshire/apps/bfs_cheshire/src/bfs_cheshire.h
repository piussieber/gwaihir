// Copyright 2024 ETH Zurich and University of Bologna.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Author: Luca Colagrande <colluca@iis.ee.ethz.ch>
// Author: Pius Sieber <pisieber@student.ethz.ch>

#include <stdint.h>
#include <math.h>

#include "args.h"
#include "snrt.h"

void frontier_job(uint32_t num_vertices, uint32_t *graph_offsets, uint32_t *graph_adjacencies, uint32_t* frontier, int32_t* dist, uint32_t* new_frontier, int32_t* new_dist) {
    // Iterate vertices
    for (uint32_t v = 0; v < num_vertices; v++) {

        // Nothing to do if vertex has already been visited
        if (dist[v] == -1) {

            // Check if any of its neighbors are in the frontier
            for (uint32_t j = graph_offsets[v]; j < graph_offsets[v+1]; j++) {

                // Get vertex ID of neighbor
                uint32_t n = graph_adjacencies[j - graph_offsets[0]];

                // Index frontier vector using vertex ID of neighbor
                uint32_t neighbor_in_frontier = (frontier[n / 32] >> (n % 32)) & 1;

                // If neighbor is in the frontier, add current vertex to new frontier
                // and update its distance
                if (neighbor_in_frontier) {
                    new_dist[v] = dist[n] + 1;
                    new_frontier[v / 32] |= 1 << (v % 32);
                    break;
                }
            }
        }
    }
}

void bfs_job(void *args) {
    uint32_t *local_new_frontier;
    int32_t *local_dist, *local_new_dist;
    bfs_args_t *local_args;

    local_args = (bfs_args_t *)args;

    // Aliases
    uint32_t num_vertices = local_args->num_vertices;
    uint32_t *frontier = (uint32_t *)(local_args->frontier_addr);
    int32_t *dist = (int32_t *)(local_args->dist_addr);
    uint32_t *out_frontier = (uint32_t *)(local_args->out_frontier_addr);
    int32_t *out_dist = (int32_t *)(local_args->out_dist_addr);

    size_t size_frontier = num_vertices / 32 * sizeof(uint32_t);
    size_t size_dist = num_vertices * sizeof(uint32_t);

    uint32_t *graph_offsets = (uint32_t *)(local_args->graph_offsets_addr);
    uint32_t *graph_adjacencies = (uint32_t *)(local_args->graph_adjacencies_addr);


    // Perform frontier calculation
    //snrt_mcycle();
    frontier_job(num_vertices, graph_offsets, graph_adjacencies, frontier, dist, out_frontier, out_dist);
    //snrt_mcycle();
}
