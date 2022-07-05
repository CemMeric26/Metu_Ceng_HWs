`timescale 1ns / 1ps 
module lab3_2(
			input[4:0] smartCode,
			input CLK, 
			input lab, //0:Digital, 1:Mera
			input [1:0] mode, //00:exit, 01:enter, 1x: idle 
			output reg [5:0] numOfStuInMera,
			output reg [5:0] numOfStuInDigital,
			output reg restrictionWarnMera,//1:show warning, 0:do not show warning
			output reg isFullMera, //1:full, 0:not full
			output reg isEmptyMera, //1: empty, 0:not empty
			output reg unlockMera,	//1:door is open, 0:closed
			output reg restrictionWarnDigital,//1:show warning, 0:do not show warning
			output reg isFullDigital, //1:full, 0:not full
			output reg isEmptyDigital, //1: empty, 0:not empty
			output reg unlockDigital //1:door is open, 0:closed
	);
	 
	// You may declare your variables below	
	//wire o1,o2;
	integer cnt,out,i;
	
	initial begin
			numOfStuInMera=0;
			numOfStuInDigital=0;
			restrictionWarnMera=0;
			isFullMera=0;
			isEmptyMera=1'b1;
			unlockMera=0;		
			restrictionWarnDigital=0;
			isFullDigital=0;
			isEmptyDigital=1'b1;
			unlockDigital=0;
	end
	//Modify the lines below to implement your design
	always @(posedge CLK)
	begin

      if(unlockMera == 1)  unlockMera = 0; 
      if(unlockDigital == 1)  unlockDigital = 0;


      //working on Mera Lab
      if(lab)	
      begin
          if(mode == 2'b01) //entering mode
          begin
             if(isFullMera)  unlockMera = 0;   //Mera is FULL 
              else   			//Mera is available
              begin
                if(numOfStuInMera < 15) 					//numofstudents under 15
                begin 
                  unlockMera = 1;
                  restrictionWarnMera=0;
                  if(numOfStuInMera==0) begin numOfStuInMera=numOfStuInMera+1; isEmptyMera=0; end  // if lab was empty now its not
				  else
                    begin numOfStuInMera=numOfStuInMera+1; end // if <15 and not empty justt increase
                end
                 else										//numofstudents over 15 check smart codes
                  begin                      
                      //this is for loop for checking odd, if any case module doesnot work
                      cnt = 0;
                      for(i=0; i<5; i = i+ 1)begin
                        if(smartCode[i] == 1'b1)  cnt = cnt+1;
                      end
                      if(cnt%2 == 0)  out = 0;
                      else  out = 1;
                      //end of odd check

                      if(out) begin  restrictionWarnMera = 1;  unlockMera=0; end     //smart code has odd number of 1's					
                      else
                      begin						
                        unlockMera = 1; restrictionWarnMera = 0;  numOfStuInMera = numOfStuInMera+1;  //Increase numof students
                        if(numOfStuInMera == 30 )    isFullMera = 1; //if number hits to 30 change isfull                        
                      end	 
                  end
              end
          end	
          
          else if(mode == 2'b00) //exiting mode
          begin
              if(isFullMera) begin  unlockMera = 1; restrictionWarnMera = 0; isFullMera = 0;  numOfStuInMera = numOfStuInMera-1;end  //if lab is full make it isfull 0 and decrease capacity
              else
              begin
                if(numOfStuInMera == 1) begin  unlockMera = 1;  isEmptyMera = 1; restrictionWarnMera = 0; numOfStuInMera = numOfStuInMera-1;end //if there is 1 student make isEmpty 1 and decrease number
                else begin  unlockMera = 1; restrictionWarnMera = 0; numOfStuInMera = numOfStuInMera-1;end  //neither full nor empty juıst decrease the capacity			
              end
          end

          else
          begin
               restrictionWarnMera = 0;
               unlockMera=0;
          end
      end

        //working on digital
      else 
      begin
          if(mode == 2'b01) //entering mode
          begin
            if(isFullDigital)  begin unlockDigital = 0;  restrictionWarnDigital=0; end//Digital is FULL 
              else   			//Digital is available
              begin
                if(numOfStuInDigital < 15) 			//numofstudents under 15
                begin 
                  unlockDigital = 1; restrictionWarnDigital=0;
                  if(numOfStuInDigital==0) 			// if student si s 0 now it will be one change isempty
                    begin
                    	numOfStuInDigital=numOfStuInDigital+1;
						isEmptyDigital=0;
                    end
                  else numOfStuInDigital=numOfStuInDigital+1;     //between (0,15)
                  
                end 
                
                else										//numofstudents over 15 check smart codes
                  begin
                      //checking odd or even function
                      cnt = 0;
                      for(i=0; i<5; i = i+ 1)begin
                       if(smartCode[i] == 1'b1)  cnt = cnt+1;
                      end
                      if(cnt%2 == 0)  out = 0;
                      else  out = 1;
                    //end of function

                      if(!out) begin  restrictionWarnDigital = 1;  unlockDigital=0; end    //smart code has even number of 1'sfor enteering Digital					
                      else
                      begin						
                         unlockDigital = 1; restrictionWarnDigital = 0;  numOfStuInDigital = numOfStuInDigital+1; //Increase numof students
                         if(numOfStuInDigital == 30)  isFullDigital = 1; 
                      end
                    
                  end
              end
          end	

          else if(mode == 2'b00) //exiting mode
          begin
              if(isFullDigital) begin  unlockDigital = 1;  isFullDigital = 0;  numOfStuInDigital = numOfStuInDigital-1;end //if lab is full make it isfull 0 and decrease capacity
              else
              begin
                if(numOfStuInDigital == 1) begin  unlockDigital = 1;  isEmptyDigital = 1;  numOfStuInDigital = numOfStuInDigital-1;end //if there is 1 student make isEmpty 1 and decrease number
                else begin  unlockDigital = 1;  numOfStuInDigital = numOfStuInDigital-1;end  //neither full nor empty juıst decrease the capacity			
              end		
          end

          else
          begin
               restrictionWarnMera = 0;
               unlockMera=0;
          end
      end
	end
	

endmodule


