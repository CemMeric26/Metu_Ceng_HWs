module PE4 where

import Data.List
import Data.Maybe

data Room = SeedStorage Int
          | Nursery Int Int
          | QueensChambers
          | Tunnel
          | Empty
          deriving Show

data Nestree = Nestree Room [Nestree] deriving Show

---------------------------------------------------------------------------------------------
------------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
--------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
--------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
---------------------------------------------------------------------------------------------

-- Note: undefined is a value that causes an error when evaluated. Replace it with
-- a viable definition! Name your arguments as you like by changing the holes: _

---------------------------------------------------------------------------------------------

-- Q1: Calculate the nutrition value of a given nest.
help_me :: [Nestree] -> Int -> Int

help_me [] total =  total
help_me (a:nt) total = help_me nt (total + nnv_calc a 0)



nnv_calc :: Nestree -> Int -> Int

nnv_calc (Nestree Empty []) total = total
nnv_calc (Nestree (SeedStorage x) []) total =  (total + x*3)
nnv_calc (Nestree (Nursery x y) []) total = (total + (x*7)+ (y*10))
nnv_calc (Nestree QueensChambers []) total = total
nnv_calc (Nestree Tunnel []) total = total
nnv_calc (Nestree Empty (a:nt)) total = help_me (a:nt) total  
nnv_calc (Nestree (SeedStorage x) (a:nt)) total = help_me (a:nt) (total + x*3) 
nnv_calc (Nestree (Nursery x y) (a:nt)) total = help_me (a:nt) (total + (x*7)+ (y*10)) 
nnv_calc (Nestree QueensChambers (a:nt)) total = help_me (a:nt) total
nnv_calc (Nestree Tunnel (a:nt)) total = help_me (a:nt) total




nestNutritionValue :: Nestree -> Int


nestNutritionValue nt = nnv_calc nt 0





-- Q2: Calculate the nutrition value of each root-to-leaf path.

calc_room (SeedStorage x) = x*3 
calc_room  (Nursery x y) = x*7 + y*10
calc_room QueensChambers = 0 
calc_room  Empty = 0 
calc_room  Tunnel = 0 






path_helper [] value_lst prev_val =  value_lst
path_helper (n:nt) value_lst prev_val = path_helper nt (value_lst ++ (calc_path_val n prev_val)) prev_val


calc_path_val (Nestree room []) val = [ val + (calc_room room)]
calc_path_val (Nestree room (n:nt)) val = path_helper (n:nt) [] (val+ (calc_room room)) 



pathNutritionValues :: Nestree -> [Int]

pathNutritionValues nt =  path_helper [nt] [] 0






-- Q3: Find the depth of the shallowest tunnel, if you can find one.

adder (Just a) (Just b) = Just (a + b)
adder Nothing (Just a) = Just a
adder (Just a) Nothing = Just a
adder Nothing Nothing = Nothing


gets (Nestree Tunnel _ ) = True
gets (Nestree _ _ ) = False

tunnel_helper [] depth = Nothing
tunnel_helper (n:nt) depth = if (gets n) then Just (depth+1) else adder (go_depth n depth) (tunnel_helper nt depth)


go_depth (Nestree Tunnel []) depth = Just (depth+1)
go_depth (Nestree Tunnel (n:nt)) depth = Just (depth+1)
go_depth (Nestree _ []) depth = Nothing
go_depth (Nestree _ (n:nt)) depth = tunnel_helper (n:nt) (depth+1)



shallowestTunnel :: Nestree -> Maybe Int
shallowestTunnel nt = tunnel_helper [nt] 0



-- Q4: Find the path to the Queen's Chambers, if such a room exists.


pathToQueen :: Nestree -> Maybe [Room]
pathToQueen nt = queen_helper [nt] [] 



get_q (Nestree QueensChambers _ ) = True
get_q (Nestree _ _ ) = False

get_room (Nestree room _) = room


add_list (Just r1) (Just r2) = Just (r1++r2)
add_list (Just r1) (Just r2) = Just (r1++r2)
frommaybe (Just x) = x
frommaybe Nothing = []

queen_helper::[Nestree] -> [Room] -> Maybe [Room]
queen_helper []  res_lst = Nothing
queen_helper (n:nt)  res_lst = if (get_q n) then (Just res_lst)  else Just (frommaybe((to_queen n (res_lst ++ [(get_room n)] ))) ++  frommaybe((queen_helper nt res_lst)))

to_queen:: Nestree -> [Room] -> Maybe [Room]
to_queen (Nestree QueensChambers [])  res_lst = Nothing
to_queen (Nestree QueensChambers (n:nt))  res_lst = Just res_lst
to_queen (Nestree room [])  res_lst = Just res_lst
to_queen (Nestree room (n:nt)) res_lst = queen_helper (n:nt) (res_lst)












-- Q5: Find the quickest depth to the Queen's Chambers, including tunnel-portation :)
quickQueenDepth :: Nestree -> Maybe Int
quickQueenDepth _ = undefined 

-- Example nest given in the PDF.
exampleNest :: Nestree
exampleNest = 
  Nestree Tunnel [
    Nestree (SeedStorage 15) [
      Nestree (SeedStorage 81) []
    ],
    Nestree (Nursery 8 16) [
      Nestree Tunnel [
        Nestree QueensChambers [
          Nestree (Nursery 25 2) []
        ]
      ]
    ],
    Nestree Tunnel [
      Nestree Empty [],
      Nestree (SeedStorage 6) [
        Nestree Empty [],
        Nestree Empty []
      ]
    ]
  ]

-- Same example tree, with tunnels replaced by Empty
exampleNestNoTunnel :: Nestree
exampleNestNoTunnel = 
  Nestree Empty [
    Nestree (SeedStorage 15) [
      Nestree (SeedStorage 81) []
    ],
    Nestree (Nursery 8 16) [
      Nestree Empty [
        Nestree QueensChambers [
          Nestree (Nursery 25 2) []
        ]
      ]
    ],
    Nestree Empty [
      Nestree Empty [],
      Nestree (SeedStorage 6) [
        Nestree Empty [],
        Nestree Empty []
      ]
    ]
  ]
