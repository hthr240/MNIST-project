from typing import List
class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        
        count = 0
        island_num = 1
        last_island = ""
        land = False

        for i in range(len(grid)):
            land = False
            for j in range(len(grid[0])):

                if i == 0:

                    if grid[i][j] == "1" and land == False:
                        land = True
                        count += 1
                        island_num += 1

                    if grid[i][j] == "1":
                        grid[i][j] = str(island_num)

                    if grid[i][j] == "0" and land == True:
                        land = False
                else:
                    if j==0:
                        island_num = int(grid[i-1][j])
                    if grid[i][j] == "0":
                        land = False

                    else:

                        if land == False: # ----------Found Land!!!-------------------
                            land = True
                            deadIsland = True
                            # count += 1
                            if grid[i-1][j] != "0": # not really new land...
                                # count -= 1
                                # if prevIsland == False:
                                last_island = grid[i-1][j]
                                grid[i][j] = grid[i-1][j]
                                continue # next cell in row
                            else: # really  new land
                                count += 1     # only here we add
                                island_num += 1
                                grid[i][j] = str(island_num)
                                continue
                        else:             # ----------Same Land:((-------------------
                            grid[i][j] = grid[i][j-1]
                            if grid[i-1][j] != "0":
                                if grid[i-1][j] == last_island:
                                    grid[i][j] = last_island
                                    grid[i][j-1] = last_island
                                else:
                                    if deadIsland:
                                        count -= 1
                                        deadIsland = False
                                    grid[i][j] = last_island
                                    if grid[i][j-1] != last_island:
                                        count = count
                            

                            
                            # if grid[i-1][j] != "0" and (last_island != grid[i-1][j] or (last_island != grid[i][j-1] and deadIsland)):
                            #     count -=1
                            #     deadIsland = False
                            #     last_island = grid[i-1][j]
                                
                                
                            
                            # elif grid[i-1][j] != "0":
                            #     grid[i][j] = grid[i-1][j]
                            #     grid[i][j-1] = grid[i][j]
        return count


                                
grid = [["1","1","1","1","1","0","1","1","1","1"],
 ["1","0","1","0","1","1","1","1","1","1"],
 ["0","1","1","1","0","1","1","1","1","1"],
 ["1","1","0","1","1","0","0","0","0","1"],
 ["1","0","1","0","1","0","0","1","0","1"],
 ["1","0","0","1","1","1","0","1","0","0"],
 ["0","0","1","0","0","1","1","1","1","0"],
 ["1","0","1","1","1","0","0","1","1","1"],
 ["1","1","1","1","1","1","1","1","0","1"],
 ["1","0","1","1","1","1","1","1","1","0"]]
        

solution = Solution()

solution.numIslands(grid)

