module PE1 where

import Text.Printf
import Data.List

-- Type synonyms --
type Point = (Double, Double)
type Signal = (Double, Double, Double, Double)

-- This function takes a Double and rounds it to 2 decimal places as requested in the PE --
getRounded :: Double -> Double
getRounded x = read s :: Double
               where s = printf "%.2f" x

-------------------------------------------------------------------------------------------
----------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------

getDistance :: Point -> Point -> Double
getDistance (x1, y1) (x2, y2) = getRounded (((abs(x1-x2))**2 + (abs(y1-y2))**2 )** 0.5)

-------------------------------------------------------------------------------------------

findAllDistances :: Point -> [Point] -> [Double]
findAllDistances b l = [getDistance b y |  y <- l]


-------------------------------------------------------------------------------------------
maxNum [x] = x
maxNum (x:x':xs) = maxNum ((if x >= x' then x else x'):xs)

minNum [x] = x
minNum (x:x':xs) = minNum ((if x <= x' then x else x'):xs)

position x xs = [i| (y,i) <- (zip xs [0..n-1]), y==x ]
    where n = length xs

findExtremes :: Point -> [Point] -> (Point, Point)
findExtremes b l = ((l !! x ),(l !! y))
    where x = ( position (minNum(findAllDistances b l)) (findAllDistances b l)) !! 0
          y =  ( position (maxNum(findAllDistances b l)) (findAllDistances b l))   !! 0


-------------------------------------------------------------------------------------------
north (a,_,_,_) = a
east (_,a,_,_) = a
south (_,_,a,_) = a
west (_,_,_,a)= a



getSingleAction :: Signal -> String
getSingleAction signal
    | ((north signal) == (south signal)) && ((east signal) == (west signal)) = "Stay"
    | ((north signal) > (south signal)) && (east signal == west signal) = "North"
    |((north signal) < (south signal)) && (east signal == west signal) = "South"
    |  ((north signal) == (south signal)) && (east signal > west signal) = "East"
    |   ((north signal) == (south signal)) && (east signal < west signal) = "West"
    | ((north signal) > (south signal)) && (east signal > west signal) = "NorthEast"
    | ((north signal) > (south signal)) && (east signal < west signal) = "NorthWest"
    |((north signal)< (south signal)) && (east signal > west signal) = "SouthEast"
    |((north signal) < (south signal)) && (east signal < west signal) = "SouthWest"
    
    
    

-------------------------------------------------------------------------------------------

getAllActions :: [Signal] -> [String]
getAllActions signals = [getSingleAction x | x<- signals ]

-------------------------------------------------------------------------------------------

numberOfGivenAction :: Num a => [Signal] -> String -> a

helpme [] action = 0
helpme (x:xs) action = if getSingleAction x == action then 1+ helpme xs action else helpme xs action
                                                            

numberOfGivenAction signals action = helpme signals action















