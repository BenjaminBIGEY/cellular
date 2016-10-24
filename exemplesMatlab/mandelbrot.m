clear;
clc;

%%% Parameters

niter=23;               % number of iterations (default: 23)
th=3;                   % threshold to determine divergence (default: 3)
reso=0.01;              % resolution (default: 0.01)


%%% Initialization

x=[-2.5:reso:1.5];      % Re range (x-axis)
y=[-1.5:reso:1.5];      % Im range (y-axis)

Lx=length(x);
Ly=length(y);

[Re,Im] = meshgrid(x,y);

Z = Re + i * Im;    % create the matrix C containing all points to be analysed.


%%% Compute the Mandelbrot set

C = zeros(Ly,Lx);   % The matrix C assigns a value to every point 
                    % with respect to the velocity of divergence.

Zn = Z;             % Initially, Z0=Z
 
for k = 1:niter
    Zn = Zn.*Zn + Z;        % run the map
    C = C + (abs(Zn)<th);   % if |Zn| > th the sequence diverges
end


%%% Figure

figure(1)
clf;

imagesc(C);
colormap(jet);

axis equal
axis off
