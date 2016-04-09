//
//  ViewController.swift
//  login
//
//  Created by ddk on 16/4/4.
//  Copyright © 2016年 ddk. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    var model = LoginBrain()

    @IBOutlet weak var userName: UITextField!
    @IBOutlet weak var pwd: UITextField!
    @IBOutlet weak var history: UITextView!
    @IBOutlet weak var msg: UILabel!
    
    @IBAction func register(sender: UIButton) {
        
    }
    @IBAction func login(sender: UIButton) {
        if(userName.text != nil && pwd.text != nil) {
            model.ShowLog(model.Check(userName.text!, pwd.text!))
        } else {
            msg.text = String("empty")
            msg.hidden = false
        }
    }
    @IBAction func cancel(sender: UIButton) {
    }
}

