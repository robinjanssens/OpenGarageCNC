thickness=3;
holeradius=3.9;
innerradius=15;
outerradius=25;
nrpulses=6;

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