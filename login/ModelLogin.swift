//
//  ModelLogin.swift
//  login
//
//  Created by ddk on 16/4/4.
//  Copyright © 2016年 ddk. All rights reserved.
//

import Foundation


class LoginBrain {
    struct userInfo {
        var id: Int
        var uname: String
        var pwd: String
    }
    
    enum ErrorType {
        case success
        case unique
        case nomatch
        case nofound
        case unknow
        
        static func copy(var dest: ErrorType, _ src: ErrorType) -> ErrorType {
            dest = src;
            return dest;
        }
    }
    
    private var lastStatus: ErrorType;
    
    private var data = [userInfo]()
    
    func  ShowMsg(id: Int) {
        for index in 0...data.count {
            if id == data[index].id {
                print(data[index])
            }
        }
    }
    
    func  ShowLog(status: ErrorType = ErrorType.unknow) {
        var type: ErrorType = status
        if(ErrorType.unknow == status) {
            type = lastStatus
        }
        switch type {
        case .success:
            print("operate success")
        case .unique:
            print("uname clash");
        case .nomatch:
            print("nomatch uname")
        case .nofound:
            print("not fount uname");
        case .unknow:
            print("unknow")
        }
    }
    
    func Check(uname: String, _ pwd: String) -> ErrorType {
        for index in 0..<data.count {
            if (uname == data[index].uname &&
                pwd == data[index].pwd) {
                return ErrorType.copy(lastStatus, ErrorType.success);
            }
        }
        return ErrorType.copy(lastStatus, ErrorType.nomatch);
    }
    
    func AddUser(uname: String, pwd: String) -> ErrorType {
        for index in 0..<data.count {
            if uname == data[index].uname {
                return ErrorType.copy(lastStatus, ErrorType.unique);
            }
        }
        data.append(userInfo(id: data.count, uname: uname, pwd: pwd))
        return ErrorType.copy(lastStatus, ErrorType.success);
    }
    
    func DelUser(uname: String) -> ErrorType {
        for index in 0..<data.count {
            if(uname == data[index].uname) {
                data.removeAtIndex(index)
                return ErrorType.copy(lastStatus, ErrorType.success);
            }
        }
        return ErrorType.copy(lastStatus, ErrorType.nofound);
    }
    
    init () {
        lastStatus = ErrorType.unknow
    }
}