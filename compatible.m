% Copyright 2012 
% This file is part of FaceRecognition
% 
% FaceRecognition is free software: you can redistribute it and/or modify
% it under the terms of the GNU General Public License as published by
% the Free Software Foundation, either version 3 of the License, or
% (at your option) any later version.
% 
% FaceRecognition is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% GNU General Public License for more details.
% 
% You should have received a copy of the GNU General Public License
% along with FaceRecognition.  If not, see <http://www.gnu.org/licenses/>.

function compatible(num)
for i=1:num
    k=imread(['tmp' num2str(i) '.jpg']);
    h(:,:,1)=imresize(k(:,:,1),[310 470]);
    h(:,:,2)=imresize(k(:,:,2),[310 470]);
    h(:,:,3)=imresize(k(:,:,3),[310 470]);
    if (i < 10)
        out1='0000';
    elseif(i >= 10 && i <100)
        out1='000';
    elseif(i >= 100 && i< 1000)
        out1='00';
    elseif(i >= 1000 && i < 10000) 
        out ='0';
    end
    imwrite(h,[out1 num2str(i) '.png']);
end