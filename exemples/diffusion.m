clear all
clc

%%% Parameters

threshold = 0.6;    % threshold
iterations = 100;    % number of iterations
cgradient = 0;      % color gradient (1=yes or 0=no)

%%% Initialization

figure(1)
clf

ax = axes('units','pixels','position',[1 1 500 400],'color','k');

text('units', 'pixels', 'position', [50,230,0],'string','Hello World!','color','w','fontname','helvetica','fontsize',100)

initial = getframe(gca);

[a,b,c]=size(initial.cdata);

z=zeros(a,b);

cells = double(initial.cdata(:,:,1)==255);
visit = z ;
sum = z;
color = (1-cgradient)*z+cgradient*(visit/iterations);

imh = image(cat(3,z,cells,color));
set(imh, 'erasemode', 'none')

%%% Run diffusion

for i=1:iterations
    sum(2:a-1,2:b-1) = cells(2:a-1,1:b-2) + cells(2:a-1,3:b) + ...
                        cells(1:a-2, 2:b-1) + cells(3:a,2:b-1) + ...
                        cells(1:a-2,1:b-2) + cells(1:a-2,3:b) + ...
                        cells(3:a,1:b-2) + cells(3:a,3:b);
    
    pick =  rand(a,b); 
    %%% edges only
    % cells = (cells & (sum<8)) | ((sum>=1) & (pick>=threshold) & (visit==0))  ;
    cells = cells  | ((sum>=1) & (pick>=threshold) & (visit==0))  ;
    visit = visit+(sum>=1) ; % (pick<threshold)  ;
    color = (1-cgradient)*z+cgradient*(visit/iterations);
   
    set(imh, 'cdata', cat(3,z,cells,color) )

    drawnow
end
