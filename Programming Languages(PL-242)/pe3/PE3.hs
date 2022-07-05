module PE3 where

-- can use these if you want to...
import Data.List
import Data.Maybe

data Private = Private { idNumber :: Int, height :: Int, timeToSwap :: Int } deriving Show

data Cell = Empty | Full Private deriving Show

type Area = [[Cell]] 

---------------------------------------------------------------------------------------------
------------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
--------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
--------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
---------------------------------------------------------------------------------------------


-- Note: undefined is a value that causes an error when evaluated. Replace it with
-- a viable definition! Name your arguments as you like by changing the holes: _


--------------------------
-- Part I: Warming up with Abstractions

-- bubbleHumans: Applying a parallel bubble step on integers.


--bubble_help [] = []
--bubble_help (x:[])=[x]
--bubble_help (x:y:xs) = if x>y then x: (bubbleHumans (y:xs)) else y:x:(bubbleHumans xs)

bubbleHumans :: [Int] -> [Int]
bubbleHumans [] = []
bubbleHumans (x:[])=[x]
bubbleHumans (x:y:xs) = if x>y then x: (bubbleHumans (y:xs)) else y:x:(bubbleHumans xs)




-- bubblePrivates: The same thing, but on privates with a key function and an asc/desc option.


bubblePrivates :: (Private -> Int) -> Bool -> [Private] -> [Private]
bubblePrivates _ _ []=[]
bubblePrivates _ _ (x:[])= [x]
bubblePrivates height True (x:y:tabur) =  if  (height x >= height y) then x:(bubblePrivates height True (y:tabur)) else y:x:(bubblePrivates height True tabur)
bubblePrivates height False (x:y:tabur) = if  (height x <= height y) then x: (bubblePrivates height False (y:tabur)) else y:x: (bubblePrivates height False tabur)
bubblePrivates idNumber True (x:y:tabur) = if  (idNumber x >= idNumber y) then x: (bubblePrivates idNumber True (y:tabur)) else y:x:(bubblePrivates idNumber True tabur)
bubblePrivates idNumber False (x:y:tabur) =if  (idNumber x <= idNumber y) then x: (bubblePrivates idNumber False (y:tabur)) else y:x:(bubblePrivates idNumber False tabur)
bubblePrivates timeToSwap True (x:y:tabur) = if  (timeToSwap x >= timeToSwap y) then x: (bubblePrivates timeToSwap True (y:tabur)) else y:x:(bubblePrivates timeToSwap True tabur)
bubblePrivates timeToSwap False (x:y:tabur) = if  (timeToSwap x <= timeToSwap y) then x: (bubblePrivates timeToSwap False (y:tabur)) else y:x:(bubblePrivates timeToSwap False tabur)

    



-- sortPrivatesByHeight: Full sort via multiple bubble steps, calculate the sorting time too!

time_comp x y time = max time (max (timeToSwap x) (timeToSwap y))



time_help [] time = time 
time_help (x:[]) time = time 
time_help (x:y:tabur) time = if  (height x >= height y) then time_help (y:tabur) time else (time_help  tabur (time_comp x y time))



sort_help tabur time = if (time_help tabur 0) /= 0 then sort_help (bubblePrivates height True tabur) (time + (time_help tabur 0) )  else (tabur,time)


sortPrivatesByHeight :: [Private] -> ([Private], Int)
sortPrivatesByHeight tabur = (sort_help tabur 0 )




--------------------------
-- Part II: Squeezing your Brain Muscles


--data Private = Private { idNumber :: Int, height :: Int, timeToSwap :: Int } deriving Show

--data Cell = Empty | Full Private deriving Show

--type Area = [[Cell]] 

-- THIS IS DIFFERENT METHOD WHICH I'VE DONE CHANGING ALL CELLS TO A PRIVATE THEN CONVERTING AGAIN TO AREA TYPE AND FOR STORTING ISSUES 
-- I MADE USE OF SORTBYPRIVATESHEIGHT FUNCTION 

construct_grid :: [Cell]-> [Private] -> [Private]
construct_grid [] priv_list = priv_list
construct_grid (Empty : grid) priv_list = construct_grid grid (priv_list ++ [(Private {idNumber = 0, height = 0, timeToSwap = 0})]) 
construct_grid (Full x : grid) priv_list = construct_grid grid (priv_list ++ [x]) 


area_construct:: [[Cell]] -> [[Private]]-> [[Private]]
area_construct [] priv_lists = priv_lists
area_construct (x:files) priv_lists = area_construct files (priv_lists ++ [(construct_grid x [])])



priv_area_sort :: [[Private]] -> [[Private]] ->  [Int] -> ([[Private]],[Int])

priv_area_sort [] new_priv_area time_list = (new_priv_area,time_list)
priv_area_sort (x:area) new_priv_area time_list = priv_area_sort area (new_priv_area ++ [(bir (sortPrivatesByHeight x ))] ) (time_list ++ [(iki (sortPrivatesByHeight x ))] )



priv_to_cell :: [Private] -> [Cell] -> [Cell]

priv_to_cell [] new_cell = new_cell
priv_to_cell (x:old_priv) new_cell = if (height x ) == 0 then priv_to_cell old_priv (new_cell ++ [Empty]) else priv_to_cell old_priv (new_cell ++ [(Full x)]) 


priv_to_area :: [[Private]] -> Area -> Area

priv_to_area [] new_area = new_area
priv_to_area (x:files) new_area = priv_to_area files (new_area ++ [(priv_to_cell x [])])


cerem_help :: Area -> (Area ,Int)
cerem_help area = (priv_to_area (bir(priv_area_sort (area_construct area []) [] [])) [] , maximum (iki(priv_area_sort (area_construct area []) [] [])))


-- ceremonialFormation: Sorting again, but with multiple files. Don't forget the time!
ceremonialFormation :: Area -> (Area, Int)
ceremonialFormation area = (cerem_help area)

--------------
--THE METHOD FOR DIRECT SORTING WITHOUT CHANGING THE DATA TYPES
-- NOT WORKING THERE IS A PROBLEM ABOUT THE MAXIMUM TIME SWAP SORTING IS WORKING COULDN'T FIND THE BUG
--------------
-- one time swap time spend calculation
time_help2 :: [Cell] -> Int -> Int 

time_help2 [] time = time 
time_help2 (Empty:[]) time = time
time_help2 ((Full x):[]) time = time
time_help2 (Empty:Empty:grid) time = time_help2 (Empty:grid) time
time_help2 (Full x:Empty:grid) time = time_help2 (Empty:grid) time 
time_help2 (Empty:Full x:grid) time = time_help2 grid (max (timeToSwap x) time)
time_help2 (Full x: Full y: grid) time = if  (height x >= height y) then time_help2 (Full y:grid) time else time_help2  grid (time_comp x y time)

--swapping action on one file 
swap_file :: [Cell] -> [Cell]

swap_file [] = []
swap_file (Empty:[]) = [Empty]
swap_file ((Full x):[])  = [(Full x)]
swap_file (Empty:Empty:grid)  = Empty: swap_file(Empty:grid)
swap_file (Empty:(Full x):grid)  = (Full x) : (swap_file (Empty:grid))
swap_file ((Full x): Empty:grid)  = (Full x) : (swap_file(Empty:grid))
swap_file ((Full x): (Full y): grid)  = if  (height x >= height y) then (Full x):(swap_file ((Full y):grid)) else (Full y): (Full x):(swap_file grid)

-- sorting a file
sortf_help:: [Cell] -> Int -> ([Cell],Int)

sortf_help grid time = if (time_help2 grid 0) /= 0 then sortf_help (swap_file grid) (time + (time_help2 grid 0)) else (grid,time)


bir (a,_)=a
iki (_,a)=a


area_help :: Area -> Area -> Int -> (Area,Int)

--area_help [] result_area time_list = (result_area, maximum time_list)
--area_help (x:files) result_area time_list = area_help files (result_area ++ [bir (sortf_help x 0)]) (time_list ++ [iki (sortf_help x 0)])

area_help [] result_area time = (result_area, time)
area_help (x:files) result_area time = area_help files (result_area ++ [bir (sortf_help x 0)]) (max time (iki (sortf_help x 0)))

----





-- swapPrivates: Swap two arbitrary privates by ID if they are in the area. Big ouch!

--changer (Full org) nw = height org     





give_id :: Private -> Int --gives the idNUmber of the private
give_id x = (idNumber x)

change_it :: Cell-> Cell ->Int->Int-> [Cell] -> [Cell]-> [Cell] -- runs over list again and using the will_change swaps the list values
change_it p1 p2 id1 id2 [] new_list = new_list
change_it p1 p2 id1 id2 (Empty :grid) new_list = change_it p1 p2 id1 id2 grid (new_list ++ [Empty])
change_it p1 p2 id1 id2 (Full x :grid) new_list 
    | (give_id x) == id1 = change_it p1 p2 id1 id2 grid (new_list ++ [p2])
    | (give_id x) == id2 = change_it p1 p2 id1 id2 grid (new_list ++ [p1])
    | otherwise = change_it p1 p2 id1 id2 grid (new_list ++ [ Full x])



swap_helper :: Int -> [Cell] -> Cell  --iterates over the area
swap_helper id1 [] = Empty
swap_helper id1 (Empty:grid)  = swap_helper id1 grid 
swap_helper id1 ((Full x):grid)  =  if (give_id x) == id1 then (Full x) else swap_helper id1 grid 


in_there :: Int -> [Cell] -> Int-> Int  --iterates over the area
in_there id1 [] count = count
in_there id1 (Empty:grid) count = in_there id1 grid count
in_there id1 ((Full x):grid) count  =  if (give_id x) == id1 then (count+1) else in_there id1 grid count



in_area:: Int-> Area -> Int -> Int
in_area id1 [] count = count
in_area id1 (x:files) count = in_area id1 files (count+ (in_there id1 x 0))


area_changer :: Area -> Cell -> Cell -> Int -> Int -> Area -> Area
area_changer [] p1 p2 id1 id2 new_area = new_area
area_changer (x:files) p1 p2 id1 id2 new_area = area_changer files p1 p2 id1 id2 (new_area ++[(change_it p1 p2 id1 id2 x [])]) 


area_swaper :: Int-> Area -> Cell
area_swaper id1 [] = Empty
area_swaper id1 (cell:files) = if (isEmpty (swap_helper id1 cell)) then (swap_helper id1 cell) else area_swaper id1 files 



swapPrivates :: Int -> Int -> Area -> Area
swapPrivates id1 id2 area = if (in_area id1 area 0)/=0 && (in_area id2 area 0)/=0 then area_changer area (area_swaper id1 area) (area_swaper id2 area) id1 id2 []  else area



isEmpty Empty= False
isEmpty _ = True


-- Best of luck to you, friend and colleague!










