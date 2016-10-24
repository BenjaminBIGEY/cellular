function LangtonsAnts()
    %% Pop-up number of ants? 
    validNrOfAnts = false; 
    while ~validNrOfAnts 
        poptitle = 'Choose number of ants'; 
        prompt={'Number of ants {1,2,...}:'};
        answer   = inputdlg(prompt,poptitle);
        nrOfAnts = str2num(answer{1}) 
        validNrOfAnts = and(round(nrOfAnts) == nrOfAnts, nrOfAnts > 0); 
    end

    %% Positioning: 

    %Manual or automatic positioning? 
    choice = questdlg('Manual positioning or automatic (random)?', ...
        'Positioning type', ...
        'Manually','Automatic','Automatic');
    switch choice
        case 'Manually';  positionType = 0
        case 'Automatic'; positionType = 1
    end

    % Initialize position(s) and direction(s) of ants(s)
    % (yep, coded with complex numbers)
    if positionType == 0 
        pos = (zeros(1,nrOfAnts));
        dir = (zeros(1,nrOfAnts));
        for k = 1:nrOfAnts 
            valid_xPos      = false; 
            valid_yPos      = false; 
            valid_direction = false; 

            while ~and(and(valid_xPos, valid_yPos), valid_direction);
                str1  = ['Ant number ' num2str(k) ]; 
                str2 = ' between {-30, 30}';
                str3  = ' [up(1) left(2) down(3) right(4)]';
                prompt={...
                    [str1 'at x-pos' str2], ... 
                    [str1 'at y-pos' str2], ...
                    [str1 'headed ' str3]};
                answer=inputdlg(prompt,'Positioning settings');

                xPos = str2num(answer{1}) 
                yPos = str2num(answer{2}) 
                aDir = str2num(answer{3}) 

                valid_xPos      = and(round(xPos)==xPos,xPos     <= 30) 
                valid_yPos      = and(round(yPos)==yPos,yPos     <= 30) 
                valid_direction = and(round(aDir)==aDir,abs(aDir-2.5)<= 2)
            end
            pos(1,k) = xPos + 1i*(yPos);
            dir(1,k) = (1i)^aDir;
        end
        N   = 4*round(max(abs(pos(:)))) + 96;
        pos = pos + N/2 + (1i*N/2);
    else
        N = 128;
        pos  =  round(N/2 + (1/8*N*(rand(1,nrOfAnts)-0.5))) + ...
             1i*round(N/2 + (1/8*N*(rand(1,nrOfAnts)-0.5)));
        dir = (1i).^round(4*rand(1,nrOfAnts)); 
    end


    validSpeed = false; 
    while ~validSpeed 
        poptitle = 'Simulation speed'; 
        prompt={'Choose pause at each frame (seconds):',...
        'Show each 1 frame? Or skip each 20 or each 400? {1 ,  20 , 400}:'};
        answer   = inputdlg(prompt,poptitle);
        pauseAfterEachFrame   = abs(str2num(answer{1})); 
        show_ant_at_iteration = str2num(answer{2}); 
        validSpeed = and(round(show_ant_at_iteration) == show_ant_at_iteration, show_ant_at_iteration > 0); 
    end

    %% Start the simulation
    % initialize walking area:
    area = zeros(N,N);
    k = 1; 
    figure;
    firstIteration = true; 
    while k < 1000000
        for antNumber = 1:nrOfAnts

            if ~firstIteration
            % set new direction:
                dir(1,antNumber) = dir(1,antNumber)*(1i)^sign(area(...
                   imag(pos(1,antNumber)), ...
                   real(pos(1,antNumber)))-0.5);
            end
            % invert color
               area(imag(pos(1,antNumber)),real(pos(1,antNumber))) = ...
                   1 - area(imag(pos(1,antNumber)), real(pos(1,antNumber)));
        end
        if firstIteration
            firstIteration = false;
        end

        % set new position:
        pos = pos + dir;

        % show at each nth iteration: 
        if ~mod(k, show_ant_at_iteration)
            imagesc(flipud(1 - area)); axis equal tight; colormap gray; hold on; 
            drawnow;
            xlabel('- no matter how unique your youth -', 'fontSize', 12); 
            ylabel('- we all end up as regular adults -', 'fontSize', 12); 
            title('Langtons Ant - Numberphile', 'fontSize', 16); 
            pause(pauseAfterEachFrame);
        end
        k = k + 1;
    end
end