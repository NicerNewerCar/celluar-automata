// const GRID_SIZE: usize = 10;

use std::vec::Vec;


fn update_world(world: &mut Vec::<Vec::<bool>>) {
    // Update the world based on the following conditions 
    // 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
    // 2. Any live cell with two or three live neighbours lives on to the next generation.
    // 3. Any live cell with more than three live neighbours dies, as if by overpopulation.
    // 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
    world[0][0] = true;
    for (r, c, val) in world.iter_mut().enumerate().flat_map(|(x, v)| v.iter_mut().enumerate().map(move |(y, v)| (x, y, v))) {
        println!("r: {r} c: {c} val: {val}");
        let alive_neighbours = 0;
        if *val {
            if alive_neighbours < 2 || alive_neighbours > 3 {
                // If cell is alive and has less than 2 or more than 3 neighbours, we flip the val
                *val = !(*val);
            }
        } else if alive_neighbours == 3 {
            // If a cell is dead and has 3 neighbours, we flip the val
            *val = !(*val);
        }
        // Otherwise it's unchanged
        println!("r: {r} c: {c} val: {val}");
    }

}

fn main() {
    // TODO: 
    // 1. Setup seed for starting
    // 2. Some display function
    // 3. Optimize the get number of neighbours function
    let mut world = Vec::<Vec::<bool>>::new();
    world.push(vec![false, true, false]);
    println!("{}", world[0][0]);
    update_world(&mut world);
    println!("{}", world[0][0]);
}
