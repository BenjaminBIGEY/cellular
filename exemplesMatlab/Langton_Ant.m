clc
clf
clear all

%%% Parameters

n=50;         % lattice size (square)
iter=5000;      % iterations

%%% Initialization

L=zeros(n,n);    % lattice (0=white; 1=black)
x=round(n/2);    % initial x-position of the ant
y=round(n/2);    % initial y-position of the ant
d=1;             % direction (1=right,2=up,3=left,4=down)

%%% Figure

imh = image(cat(3,L,L,L));
set(imh, 'erasemode', 'none')
axis equal
axis tight
set(gca,'XTickLabel',{''})  % to remove x tick labels
set(gca,'YTickLabel',{''})  % to remove y tick labels
set(gca,'XTick',[])         % to remove x ticks
set(gca,'YTick',[])         % to remove y ticks
  
%%% Run

for i=1:iter
    
    if(L(x,y)==0)       % if white
       d=mod(d-2,4)+1;  % turn 90° right
       L(x,y)=1;       % flip the color of the square
    else
       d=mod(d,4)+1;    % turn 90° left
       L(x,y)=0;       % flip the color of the square
    end

    x=(d==1)*(x+1)+(d==2)*x+(d==3)*(x-1)+(d==4)*x;
    y=(d==1)*y+(d==2)*(y+1)+(d==3)*y+(d==4)*(y-1);
         
    A=L; A(x,y)=0.8;   % position of the ant (red)
    
    set(imh, 'cdata', cat(3,A,L,L) )

    drawnow

end