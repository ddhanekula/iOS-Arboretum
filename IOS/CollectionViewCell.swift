//
//  CollectionViewCell.swift
//  IOS
//
//  Created by Naresh kumar Nagulavancha on 11/15/15.
//  Copyright © 2015 Student. All rights reserved.
//

import UIKit

class CollectionViewCell: UICollectionViewCell
{
    @IBOutlet weak var imageview: UIImageView!
   // var myimage = UIImage(named: "Cancel_Upload")
    func getphoto(photo:String)
    {
        let image=NSData(contentsOfURL: NSURL(string:photo)!)
        
        imageview.image =
        UIImage(data:image!)
        
    }

}
