clear all;
clc;

%% function to minimize, search space
f=@(x1,x2) -20*exp(-0.2*sqrt(0.5*(x1.^2+(x2-1).^2)))-exp(0.5*(cos(2*pi*x1)+cos(2*pi*(x2-1))));
f_vect=@(x) f(x(:,1),x(:,2));
xlims=[-4 4 ; -3 5];

%% optimization parameters
NP=20;      % population size (NP>=4)
CR=0.5;     % crossover probability (CR=0...1)
F=1;        % differential weight (F=0...2)
maxiter=50; % number of iterations

%% differential evolution optimization
dim=size(xlims,1);
% initialize all agents with random positions in the search space
x=repmat(xlims(:,1)',NP,1)+repmat((xlims(:,2)-xlims(:,1))',NP,1).*rand(NP,dim);
% iterate until stopping criterion is reached
for ii=1:maxiter
    % iterate over all candidates
    for xi=1:NP
        % pick 3 distinct agents at random
        agents=randperm(NP,4);
        if any(agents==xi)
            agents(agents==xi)=[];
        else
            agents(4)=[];
        end
        agents=x(agents,:);
        % attempt to mutate agent x_i
        matchInd=rand(1,dim)<CR;
        matchInd(randi(dim))=1;
        y=x(xi,:);
        y(matchInd)=agents(1,matchInd)+F*(agents(2,matchInd)-agents(3,matchInd));
        if f_vect(y)<f_vect(x(xi,:))
            x(xi,:)=y;
        end
    end
    % plot
    figure(1);
    plot(0:NP-1,x);
    axis([0 NP-1 min(xlims(:,1)) max(xlims(:,2))]);
    xlabel('i');
    xlabel('x_i');
    title(sprintf('Iteration %d of %d',ii,maxiter));
    pause(0.05);
    drawnow;
end
[~,ind]=min(f_vect(x));
x=x(ind,:)

%% plot
x1=linspace(xlims(1,1),xlims(1,2),100);
x2=linspace(xlims(2,1),xlims(2,2),100);
[X1,X2]=meshgrid(x1,x2);
figure(2);
surf(x1,x2,f(X1,X2));
%shading interp;
colormap('copper');
hold on;
plot3(x(:,1),x(:,2),f_vect(x),'ro','MarkerSize',20);
hold off;
xlabel('x_1');
ylabel('x_2');
zlabel('f(x_1, x_2)');