#!/usr/local/bin/perl

use 5.010;
use utf8

chdir "./build";
system("cmake ..");
system("make");
chdir "..";

