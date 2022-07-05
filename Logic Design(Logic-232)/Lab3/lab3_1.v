`timescale 1ns / 1ps

module ab(input A, input B, input clk, output reg Q);

    initial Q = 0;
	 
	 always@(posedge clk)
	  case({A,B})
	   2'b00: Q<=Q;
	   2'b01: Q<=1;
	   2'b10: Q<=0;
	   2'b11: Q<=~Q;
	  endcase
	 

endmodule

module ic1337(// Inputs
              input I0,
              input I1,
              input I2,
              input clk,
              // Outputs
              output Q0,
              output Q1,
              output Z);

    // You can implement your code here
    // ...
	 
	 wire O1,O2;
	 wire A1,B1,A2,B2;
	 

	 assign A1 = (~(I0 | ~I1)) & ~I2;
	 assign B1 = I2;
	 assign A2 = ~I2;
	 assign B2 = (~(I2 | ~I1)) ~^ I0 ;
	 
	 
	 ab ab1(A1,B1,clk,O1);
	 ab ab2(A2,B2,clk,O2);
	 
	 assign Q0=O1;
	 assign Q1=O2;
	 assign Z = Q0^Q1;
	 


endmodule
