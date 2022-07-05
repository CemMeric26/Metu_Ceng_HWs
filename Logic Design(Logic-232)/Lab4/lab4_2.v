// Code your design here
`timescale 1ns / 1ps

module lab4_2(// INPUTS
              input wire      mode,
              input wire[2:0] opCode,
              input wire[3:0] value,
              input clk,
              input reset,
              // OUTPUTS
              output reg[9:0] result,
              output reg cacheFull,
              output reg invalidOp,
              output reg overflow);

    //================//
    // INITIAL BLOCK  //
    //================//
    //Modify the lines below to implement your design
    integer i,j,count,index,temp,temp2,high,check,setr; 
	 reg [2:0] ins_cache[31:0];
	 reg [3:0] val_cache[31:0];
	 reg [9:0] p0;
	 reg [9:0] p1;
	 
	 
	 initial begin

        // ...
		  //result=0;
		  cacheFull=0;
		  invalidOp=0;
		  overflow=0;
		  p0=0;
		  p1=0;
			count=0; 
			index=0;
			setr=0;

    end

    //================//
    //      LOGIC     //
    //================//
    //Modify the lines below to implement your design
	 
	 
    always @(posedge clk or posedge reset)
    begin

        if(reset==1)
		  begin  //reset op began, it will take everything to the intial state
				cacheFull=0;
				invalidOp=0;
				overflow=0;
				p0=0;
				p1=0;
				count=0;
				index=0;
				setr=0;
				for(i=0;i<=31;i=i+1)
				begin
					ins_cache[i]=0;
				end
				for(i=0;i<=31;i=i+1)
				begin
				val_cache[i]=0;
				end
				result=0;
				
		  end   //reset op end
		  
		  else //not reset working with clock
		  begin
				if(mode==0)
				begin // LOAD MODE OP BEGAN
					if(count==32) //no more instruction
					begin
						cacheFull=1;
					end
					else
					begin //loading instructions and value to their caches
						if(opCode==3'b011)
						begin
							invalidOp=1;
						end
						else if(opCode==3'b111)
						begin
							invalidOp=1;
						end
						else
						begin
							ins_cache[count]= opCode;
							val_cache[count]= value;
							count=count+1;
							invalidOp=0;
						end
	
					end
					
				end // LOAD MODE OP END
				
				else
				begin //CALCULATE MODE OP BEGAN
					if(ins_cache[index]==3'b000) //ADD OP
						begin
							//temp=result;
							//temp2=p0;
							check=val_cache[index] + p0;
							if(check>1023) //overflow check
							begin
								result=check-1024;
								overflow=1;
							end
							else
							begin
								result= val_cache[index] + p0;
								overflow=0;
							end							
							//p0=temp;
							//p1=temp2;
							p1=p0;
							p0=result;
							if(index==count-1)
							begin
								index=setr;
							end
							else
							begin
								index=index+1;
							end
							
						end //add op end
						
						else if(ins_cache[index]==3'b001) //ADD2 OP
						begin
							//temp=result;
							//temp2=p0;							
							check= val_cache[index] + p0+p1;
							if(check>1023) //overflow check
							begin
								result=check-1024;
								overflow=1;
							end
							else
							begin
								result= val_cache[index] + p0+p1;
								overflow=0;
							end   //checking ended
							//p0=temp;
							//p1=temp2;
							p1=p0;
							p0=result;
							if(index==count-1)
							begin
								index=setr;
							end							
							else
							begin
								index=index+1;
							end
		
						end // add2 op end
						
						else if(ins_cache[index]==3'b010) //FMA OP
						begin
							//temp=result;
							//temp2=p0;							
							check = val_cache[index] + (p0*p1);
							if(check>1023) //overflow check
							begin
								result=check-1024;
								overflow=1;
							end
							else
							begin
								result= val_cache[index] + (p0*p1);
								overflow=0;
							end   //checking ended
							//p0=temp;
							//p1=temp2;
							if(index==count-1)
							begin
								index=setr;
							end							
							begin
								index=index+1;
							end
							p1=p0;
							p0=result;
						end //fma op end
						
						else if(ins_cache[index]== 3'b100) //POPC OP 
						begin
							temp=p0;
							high=0;
							for(j = 0; j < 10; j = j + 1) // counting how many 1's in p0
							begin														
								if(temp % 2 == 1)
								begin
									high= high+1;
								end
								temp = temp / 2;
							end
							overflow=0;  // after this there cant be any overflow
							temp=result;
							temp2=p0;							
							result= high;
							p0=temp;
							p1=temp2;
                     high=0;
							if(index==count-1)
							begin
								index=setr;
							end
							
							else
							begin
								index=index+1;
							end
						end // popc op end
						
						else if(ins_cache[index]==3'b101)//BREV OP
						begin
							temp=result;
							temp2=p0;
							for(j=0;j<10;j=j+1)
							begin
                           result[j]=p0[9-j];
							end
							p0=temp;
							p1=temp2;
							overflow=0;
							if(index==count-1)
							begin
								index=setr;
							end
							
							else
							begin
								index=index+1;
							end
							
						end // brev op end
						
						else if(ins_cache[index]==3'b110) //// SETR OP
						begin
							setr = val_cache[index];
							if(index == count-1)
							begin
								index=setr;
							end
							else
							begin
								index=index+1;
							end
							overflow=0;
						end // setr op end
						else //ILLEGAL OP 
						begin
							result=result;
						end  //illegeal end
				end  //CALCULATE MODE OP BEGAN
				
				
		  end  // clock operation end

    end   //always block end
endmodule
