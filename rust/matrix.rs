// Auto generated from the C version by ChatGPT.

struct Matrix {
    nrows: usize,
    ncols: usize,
    entries: Vec<f64>,
}

impl Matrix {
    fn new(nrows: usize, ncols: usize) -> Matrix {
        Matrix {
            nrows,
            ncols,
            entries: vec![0.0; nrows * ncols],
        }
    }

    fn init(&mut self) {
        for i in 0..self.nrows * self.ncols {
            self.entries[i] = (i + 1) as f64;
        }
    }

    fn print(&self) {
        for i in 0..self.nrows * self.ncols {
            print!("{:7.2}", self.entries[i]);
            if i % self.ncols == self.ncols - 1 {
                println!();
            }
        }
    }

    fn diag(&mut self, s: &Matrix) {
        if self.nrows != s.nrows || self.ncols != s.ncols {
            eprintln!("diag: Matrices of different sizes");
            std::process::exit(1);
        }
        for i in 0..s.nrows {
            for j in 0..s.ncols {
                if i == j {
                    self.entries[i * s.ncols + j] = s.entries[i * s.ncols + j];
                } else {
                    self.entries[i * s.ncols + j] = 0.0;
                }
            }
        }
    }

    fn ldiag(&mut self, s: &Matrix) {
        if self.nrows != s.nrows || self.ncols != s.ncols {
            eprintln!("ldiag: Matrices of different sizes");
            std::process::exit(1);
        }
        for i in 0..s.nrows {
            for j in 0..s.ncols {
                if i > j {
                    self.entries[i * s.ncols + j] = s.entries[i * s.ncols + j];
                } else {
                    self.entries[i * s.ncols + j] = 0.0;
                }
            }
        }
    }
}

fn main() {

    let args: Vec<String> = std::env::args().collect();

    if args.len() != 3 {
        println!("Usage: {} <nrows> <ncols>", args[0]);
        std::process::exit(1);
    }

    let nrows: usize = args[1].parse().unwrap();
    let ncols: usize = args[2].parse().unwrap();

    let mut m = Matrix::new(nrows, ncols);
    m.init();

    let mut md = Matrix::new(nrows, ncols);
    md.diag(&m);

    let mut mld = Matrix::new(nrows, ncols);
    mld.ldiag(&m);

    println!("\nm:");
    m.print();
    println!("\ndiag(m):");
    md.print();
    println!("\nldiag(m):");
    mld.print();
    println!();
}
