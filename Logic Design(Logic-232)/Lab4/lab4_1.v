`timescale 1ns / 1ps
module lab4ROM (input [3:0] romAddr, output reg[4:0] romOutput);

  always@(romAddr) begin
    if(romAddr==0) begin assign romOutput= 5'b00000; end
    else if(romAddr==1) begin assign romOutput=5'b00001; end
    else if(romAddr==2) begin assign romOutput=5'b00110; end
    else if(romAddr==3) begin assign romOutput=5'b00111; end
    else if(romAddr==4) begin assign romOutput=5'b01011; end
    else if(romAddr==5) begin assign romOutput=5'b01100; end
    else if(romAddr==6) begin assign romOutput=5'b01101; end
    else if(romAddr==7) begin assign romOutput=5'b01110; end
    else if(romAddr==8) begin assign romOutput=5'b11101; end
    else if(romAddr==9) begin assign romOutput=5'b11110; end
    else if(romAddr==10) begin assign romOutput=5'b11111; end
    else if(romAddr==11) begin assign romOutput=5'b10000; end
    else if(romAddr==12) begin assign romOutput=5'b10111; end
    else if(romAddr==13) begin assign romOutput=5'b11000; end
    else if(romAddr==14) begin assign romOutput=5'b11001; end
    else begin assign romOutput=5'b11010; end
    end
      
      
  
endmodule
																							
module lab4RAM (
	input ramMode, //0:read, 1:write
	input [3:0] ramAddr, 
	input [4:0] ramInput,
	input  ramOp, //0:polynomial, 1:derivative
	input [1:0] ramArg,  //00:+1, 01:+2, 10:-1, 11:-2
	input CLK, 
	output reg [8:0] ramOutput);

  reg [8:0] memory_ram[15:0];
  integer mem_dec;
  integer i;
  
  initial 
    begin
	for(i = 0; i <= 15; i = i + 1)
	begin
		memory_ram[i] = 9'b000000000;
	end
	end
  

  
  always@(ramMode,ramAddr,ramInput,ramOp,ramArg)
begin
  if(ramMode == 0)
	begin
		mem_dec = ramAddr;
      ramOutput = memory_ram[mem_dec];
	end
end
  
  
  integer d4,d3,d2,d1,d0,x,j;
  always@(posedge CLK)
    begin
      if(ramMode==1)
        begin  //write start
          mem_dec= ramAddr;
          
          if(ramOp==0) //poynomial value will be evaluated
            begin
              
              if(ramArg==2'b00) //+1
                begin
                  x=0;
                  for(i=0;i<5;i=i+1)
                  begin
                    if(ramInput[i]==1)
                      begin
                        x=x-1;
                      end
							else
							begin
								x=x+1;
							end
                  end
                  
                  /* x value is in decimal convert it to binary and write it to the ram addrees*/
                  //if our number is negative
					if(x<0)
					begin
					x= (-x)+256;
					end
                
                for(j = 0; j < 9; j = j + 1)
					begin
                  		memory_ram[mem_dec][j] = x % 2;
						x = x / 2;
					end
                  
                  
                end  // end off +1 arguement
              
              else if(ramArg == 2'b01) //+2
              begin
                x=0;
                if(ramInput[4]==1)
                  begin
                    x=x-16;
                  end
					else
					begin
						x=x+16;
					end
                if(ramInput[3]==1)
                  begin
                    x=x-8;
                  end
						else
					begin
						x=x+8;
					end
                if(ramInput[2]==1)
                  begin
                    x=x-4;
                  end
						else
					begin
						x=x+4;
					end
                if(ramInput[1]==1)
                  begin
                    x=x-2;
                  end
						else
					begin
						x=x+2;
					end
                if(ramInput[0]==1)
                  begin
                    x=x-1;
                  end
						else
					begin
						x=x+1;
					end
						
					//if our number is negative
					if(x<0)
					begin
					x= (-x)+256;
					end
                
                for(j = 0; j < 9; j = j + 1)
					begin
                  memory_ram[mem_dec][j] = x % 2;
						x = x / 2;
					end
                
                
              end // end of +2
              
              else if(ramArg == 2'b10) //-1
                begin
                  x=0;
                  if(ramInput[4]==1)
                  begin
                    x=x-1;
                  end
                  else
                    begin
                      x=x+1;
                    end
                  
                if(ramInput[3]==1)
                  begin
                    x=x+1;
                  end
                else
                  begin
                    x=x-1;
                  end
                 
                if(ramInput[2]==1)
                  begin
                    x=x-1;
                  end
                else
                  begin
                    x=x+1;
                  end
                if(ramInput[1]==1)
                  begin
                    x=x+1;
                  end
                 else
                   begin
                     x=x-1;
                   end
                 
                if(ramInput[0]==1)
                  begin
                    x=x-1;
                  end
                 else
                   begin 
                     x=x+1;
                   end
						//if our number is negative
					if(x<0)
					begin
					x= (-x)+256;
					end
                
                for(j = 0; j < 9; j = j + 1)
					begin
                  		memory_ram[mem_dec][j] = x % 2;
						x = x / 2;
					end
      
                end //endof -1 arg
              
              else //-2
                begin
                   x=0;
                  if(ramInput[4]==1)
                  begin
                    x=x-16;
                  end
                  else
                    begin
                      x=x+16;
                    end
                  
                if(ramInput[3]==1)
                  begin
                    x=x+8;
                  end
                else
                  begin
                    x=x-8;
                  end
                 
                if(ramInput[2]==1)
                  begin
                    x=x-4;
                  end
                else
                  begin
                    x=x+4;
                  end
                if(ramInput[1]==1)
                  begin
                    x=x+2;
                  end
                 else
                   begin
                     x=x-2;
                   end
                 
                if(ramInput[0]==1)
                  begin
                    x=x-1;
                  end
                 else
                   begin 
                     x=x+1;
                   end 

					//if our number is negative
						if(x<0)
						begin
						x= (-x)+256;
						end
						 
						 for(j = 0; j < 9; j = j + 1)
						begin
									memory_ram[mem_dec][j] = x % 2;
							x = x / 2;
						end
					
               end // end of -2
					 
            end //ram polynomial operation end
        
		  else //derivaitive operation begin
		  begin
			if(ramArg==2'b00) // +1 operation start
			begin
				d4=4;
				d3=3;
				d2=2;
				d1=1;
			end // +1 op end
			
			else if(ramArg==2'b01) // +2 op start
			begin
				d4 = 4*(2**3);
				d3 = 3*(2**2);
				d2 = 2*(2);
				d1 = 1;
			
			end //+2 op end
			
			else if(ramArg==2'b10) // -1 op start
			begin
				d4 = -4;
				d3 =  3;
				d2 = -2;
				d1= 1;
			end //-1 op end
			
			else    // -2 op start
			begin
				d4 = 4*((-2)**3);
				d3 = 3*((-2)**2);
				d2 = 2*(-2);
				d1=1;
			end  //-2 op end
			if(ramInput[4] ==1)
			begin
				d4= -d4;
			end
			if(ramInput[3] ==1)
			begin
				d3= -d3;
			end
			if(ramInput[2] ==1)
			begin
				d2= -d2;
			end
			if(ramInput[1] ==1)
			begin
				d1= -d1;
			end
			
			x=d4+d3+d2+d1;
			if(x<0)
			begin
			 x= (-x)+256;
			end
			for(j = 0; j < 9; j = j + 1)
			begin
				memory_ram[mem_dec][j] = x % 2;
				x = x / 2;
			end
			
		  end //derivaitve operation end
          
        end //write operation end
      
      
      
      
      
    end
  
  
  

endmodule


module polMEM(input mode, input [3:0] memAddr, input op, input [1:0] arg, input CLK, output wire [8:0] memOutput);


	wire [4:0]  romOutput;

	lab4ROM RO(memAddr, romOutput);
	lab4RAM RA(mode, memAddr, romOutput, op, arg, CLK, memOutput);



endmodule
