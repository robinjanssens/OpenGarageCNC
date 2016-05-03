//========================================
//
//   Speed Encoder
//   Copyright (C) 2016  Open Garage
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 3 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software Foundation,
//   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
//
//========================================

thickness=1;
holeradius=4;
innerradius=15;
outerradius=25;
nrpulses=12;

fillangle=360/nrpulses/2;
spacing=0.1;

difference() {
    union() {
        cylinder(h = thickness, r = innerradius);
        intersection() {
            cylinder(h = thickness, r = outerradius);
            for(angle = [0:1:nrpulses]) {
                rotate([0, 0, fillangle * angle * 2])
                difference() {
                    rotate([0, 0, fillangle]) translate([0, 0, -spacing]) cube([outerradius + spacing, outerradius + spacing, thickness + spacing * 2]);
                    translate([0, 0, -spacing]) cube([outerradius + spacing, outerradius + spacing +10, thickness + spacing * 2]);
                }
            }
        }
    }
    translate([0, 0, -spacing]) cylinder(h = thickness + spacing * 2, r = holeradius);
}
