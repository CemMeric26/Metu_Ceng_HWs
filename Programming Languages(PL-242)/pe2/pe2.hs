module PE2 where

import Text.Printf

type Point = (Int, Int)
type Dimensions = (Int, Int)
type Vector = (Int, Int)

getRounded :: Double -> Double
getRounded x = read s :: Double
               where s = printf "%.2f" x

castIntToDouble x = (fromIntegral x) :: Double

-------------------------------------------------------------------------------------------
----------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------
getVector :: String -> Vector
getVector d 
    | d=="Stay" = (0,0)
    | d=="North" = (0,1)
    | d=="South" = (0,-1)
    | d=="East" = (1,0)
    | d=="West" = (-1,0)
    | d=="NorthEast" = (1,1)
    | d=="NorthWest" = (-1,1)
    | d=="SouthEast" = (1,-1)
    | d== "SouthWest" =(-1,-1)
    

-------------------------------------------------------------------------------------------------------------------------------
getAllVectors :: [String] -> [Vector]
getAllVectors l = [getVector x | x <- l ]

-------------------------------------------------------------------------------------------------------------------------------


add (x, y) (u, v) = (x+u, y+v)
            
produce prev [] result = result++ [prev]
produce prev (x:liste) result = produce (add x prev) liste (result ++ [prev])



producePath :: Point -> [String] -> [Point]
producePath initial actions = produce initial (getAllVectors actions) []

-------------------------------------------------------------------------------------------------------------------------------
bir (a,_)=a
iki (_,a)=a

my_compare p1 p2 = if ( ( (bir p1) > (bir p2) && (iki p1) > (iki p2)) &&  ((bir p2) >= 0 && (iki p2) >= 0) ) then True else False 

takePathInArea :: [Point] -> Dimensions -> [Point]
takePathInArea path (bx, by) =  takeWhile ( my_compare (bx,by) ) path



-------------------------------------------------------------------------------------------------------------------------------

is_equal p1 p2 = if (bir p1 == bir p2) && (iki p1 == iki p2) then True else False

isMember n [] = False
isMember n (x:xs)
    | (is_equal n x) = True
    | otherwise = isMember n xs


 


remainingObjects :: [Point] -> Dimensions -> [Point] -> [Point]
remainingObjects path border objects = [x | x <- objects, not (isMember x (takePathInArea path border) )  ]







-------------------------------------------------------------------------------------------------------------------------------

calculate [] border objects steps count = getRounded(castIntToDouble(steps)/castIntToDouble(count))
calculate (i:paths) border objects steps count = if ((length i == length (takePathInArea i border)) && (remainingObjects i border objects) == [] ) then (calculate paths border objects (steps + (length i) ) (count+1)) else (calculate paths border objects (steps) (count)) 


averageStepsInSuccess :: [[Point]] -> Dimensions -> [Point] -> Double
averageStepsInSuccess paths border objects = calculate paths border objects 0 0



















