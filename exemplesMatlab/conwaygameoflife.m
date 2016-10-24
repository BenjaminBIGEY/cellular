clear;
clc;


%%% key parameters:

s=50;            % size of the grid (square s x s) - default: 50
n=300;           % number of initial living cells - default: 300
niter=40;        % number of iterations - default: 40


%%% additional parameters:

ms=5;           % margin size (to account to what happens just out of the border) - default: 5
speed=0.2;      % speed (number of seconds/frame) - default: 0.4


%%% total size of the grid and total number of living cells:

ts=s+2*ms;         % size of the full grid
tn=n*(ts^2/s^2);   % number of living cells in the full grid


%%% generate random pattern:

k=ceil(ts^2.*rand(tn,1));   % random


%%% pre-defined initial pattern:

%s=10; ms=1; ts=s+2*ms; niter=8; k=[53,54,65];                % stable block
%s=10; ms=1; ts=s+2*ms; niter=10; k=[53,54,55];                % blinker (periodic pattern)
%s=10; ms=1; ts=s+2*ms; niter=8; k=[53,54,55,64,65,66];       % toad (periodic pattern)
%s=20; ms=5; ts=s+2*ms; niter=70; k=[188,219,247,248,249];    % glider (spaceship)
%s=20; ms=5; ts=s+2*ms; niter=30; k=[193,195,226,256,283,286,314,315,316];  % glider (spaceship)
%s=40; ms=5; ts=s+2*ms; niter=120; speed=0.05; k=[870,871,874,920,923,970,973,974,1022,1070,1072,1073,1074];  % growing growing

%%% generate initial matrix

M=zeros(ts);
M(k)=1;


%%% run the game

figure(1);
clf;

for i=0:niter
   fprintf('.');
   pause(speed);
   if i>0
   M=update(M);
   end
   Mout=ones(s)-M([ms:end-ms-1],[ms:end-ms-1]);
   h=imagesc(Mout);
   colormap(gray);
   set(gca,'XTickLabel',{''})    % to remove x tick labels
   set(gca,'YTickLabel',{''})    % to remove y tick labels
   set(gca,'XTick',[0.5:1:s])    % to remove x ticks
   set(gca,'YTick',[0.5:1:s])    % to remove y ticks
   grid on
   
   if i < 10
      myfile = sprintf('frame0%d.jpg',i);
   else
      myfile = sprintf('frame%d.jpg',i);
   end
   r=5;  % resolution
   Msav=resolution(Mout,r);
   imwrite(Msav,myfile,'jpg','quality',100);
   
%   P(i+1)=getframe;   % used for the movie

end

fprintf('\n\n');

%%% show the movie

% fprintf('play the movie...\n');
% 
% mplay=1;      % number of time the movie is played
% mspeed=1;     % speed of the movie (number of frames/second)
% 
% figure(2)
% clf;
% movie(P,mplay,mspeed)
% 
% fprintf('save the movie...\n');
% 
% movie2avi(P,'test.avi') 
% 
% fprintf('finished!\n');



% ==================================================
% Update matrix
% ==================================================

function P=update(M);

%% Rules of the Game of Life (Conway):
%% Each living cell with 0 or 1 neighbors dies (loneliness)
%% Each living cell with 4 or more neighbors dies (overpopulation).
%% Each dead cell with 2 or 3 neighbors get to life.

s=length(M);
P=zeros(s);

for i=2:s-1
  for j=2:s-1
      nn=M(i-1,j-1)+M(i,j-1)+M(i+1,j-1)+M(i-1,j)+M(i+1,j)+M(i-1,j+1)+M(i,j+1)+M(i+1,j+1);   % number of neighbourgs
      if(M(i,j)==0 && nn == 3)
          P(i,j)=1;
      elseif(M(i,j)==1 && nn >= 2 && nn <= 3)
          P(i,j)=1;
      end
  end
end


end


% ==================================================
% Resolution
% ==================================================

function P=resolution(M,r);

%% I didn't find any matlab option to increase the resolution when saving
%% an image in a jpg file. So I created this little function that converts
%% a n x n matrix into a n*r x n*r matrix

n=length(M);      % size of the original matrix
nr=n*r;           % size of the new matrix
P=zeros(nr);      % initialization of the new matrix

for i=1:n
  for j=1:n
     for k=(i-1)*r+1:i*r
        for p=(j-1)*r+1:j*r
            P(k,p)=M(i,j);
        end
     end
  end
end


end