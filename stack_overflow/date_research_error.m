% Goal of the script:
% 1)read my .xlsx files from my directory
% 2)creat date for missed dates in a date columns
% 3)set NaN for variables in these dates
% 4) fill some columns with the next good value and fill some columns with an average of some other columns.

% Clear up the workspace, the figures and the command window feed
clear
close all
clc

directory = 'C:\Users\Behzad\Desktop\New folder (2)';
filePattern = fullfile(directory, '*.xlsx');
file = dir(filePattern);
all_tables = cell(1,length(file));
for k = 1 : numel(file)
    baseFileName = file(k).name;
    fullFilename = fullfile(directory, baseFileName);
    
    fprintf('Processing file %s\n', fullFilename);
    all_tables{k} = process_xlsx(fullFilename);
end



function [current_table] = process_xlsx(filename)
    current_table = readtable(filename);

    current_table = fillmissing(current_table, 'next', 'DataVariables', {'lat', 'lon', 'station_elevation'});

    % If one of the value tmax and tmin is NaN the mean will stay NaN
    mean_tm =  mean([current_table.tmax_m(isnan(current_table.tm_m)), current_table.tmin_m(isnan(current_table.tm_m))],2);
    current_table.tm_m(isnan(current_table.tm_m)) = mean_tm;


    % Create a list of all the dates between start date and end date
    start_date = datetime([1982 01 01]);
    end_date = datetime([2018 12 31]);
    allDates = (start_date : calmonths(1) : end_date).';
    allDates.Format = 'yyyy-dd-MM';

    missing_dates = allDates(~ismember(allDates,current_table.data));
    nan_values = NaN(sum(~ismember(allDates,current_table.data)),1);
    variable_names = {'data','value'};
    tempTable = table(missing_dates, nan_values,'VariableNames',variable_names);
    current_table = outerjoin(current_table,tempTable,'MergeKeys', 1);

    current_table = sortrows(current_table, 8); 
end